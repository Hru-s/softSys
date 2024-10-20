#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include<fcntl.h>
#include<cstring>
#include<iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

struct account{
    string passwd;
    int balance;
    int active;
};

struct empAccount{
    string passwd;  
};

struct adminAccount{
    string passwd;  
};

///////////////
string getCurrentDateTime();
int fileExists(string &path);
void addHistory(string &name,string &msg);
void customerHandler(string name,int nsd);
void getInfo(int fd,account &acc);
void setInfo(int fd,account &acc);
void getBalance(string &name);
void deposit(string &name,int nsd);
void withdraw(string &x,int nsd);
void applyLoan(string &name,int nsd);
void changePasswd(string &path,int nsd);

void customerHandler(string name,int nsd);
void employeeHandler(string name,int nsd);
void managerHandler(string name,int nsd);
void adminHandler(string name,int nsd);

void changeActive(int nsd);
///////////////

string getCurrentDateTime() {

    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Format date and time as a string
    ostringstream oss;
    oss << put_time(ltm, "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}

void addHistory(string &name,string &msg)
{
    string path = "./history/" + name;
    int fd = open(path.c_str(),O_WRONLY);
    msg = msg + "\n";
    if (lseek(fd, 0, SEEK_END) < 0) {
        perror("Error seeking to end of file");
        close(fd);
    }

    int bytes_written = write(fd, msg.c_str(), msg.size());
    if (bytes_written < 0) {
        perror("Error writing to file");
        close(fd);
    }

    close(fd);
}

void getInfo(string name,account &acc)
{
    
    string path = "./customerAccounts/" + name;
    int fd = open(path.c_str(),O_RDONLY, 0666);
    
    char buff[1024];
    int size=0;
    string line;
    int pos=0;
    while ((size = read(fd, buff, sizeof(buff))) > 0) 
    {    line.append(buff, size);}
    //get password
        pos= line.find("\n");
        //strncpy(acc.passwd, line.substr(0, pos).c_str(), sizeof(acc.passwd) - 1);
        //acc.passwd[sizeof(acc.passwd) - 1] = '\0';
        acc.passwd=line.substr(0,pos);
        line=line.substr(pos+1);
    //get balance
        pos=line.find("\n");
        acc.balance=stoi(line.substr(0,pos));
    //get active
        acc.active=stoi(line.substr(pos+1));
}

void setInfo(string name,account &acc)
{
    
    string path = "./customerAccounts/" + name;
    int fd = open(path.c_str(),O_RDWR | O_CREAT |O_TRUNC, 0666);
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    
    // Use sprintf to format and append each field
    snprintf(buff, 1024, "%s\n%d\n%d", acc.passwd.c_str(), acc.balance, acc.active);

    int bytes = write(fd, buff, strlen(buff));
    if (bytes < 0) {
        std::cerr << "Error writing to file." << std::endl;
    } 

    close(fd);
}

void getBalance(string &name,int nsd)
{
    account acc;

    getInfo(name,acc);

    string msg=to_string(acc.balance);
    write(nsd,msg.c_str(),msg.size());
    
}

void deposit(string &name,int nsd)
{
    account acc;
    char buff[1000];
    int bytesRead=0;
    string msg="enter amount;\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string add(buff);
    getInfo(name,acc);
    if(acc.active)
    {   acc.balance+=stoi(add);
        setInfo(name,acc);
        string msg= "deposited "+add;
        addHistory(name,msg);
    }
    else cout<<"acc is deactive"<<endl;

}

void withdraw(string &x,int nsd)
{
    account acc;
    getInfo(x,acc);
    char buff[1000];
    int bytesRead=0;
    string msg="enter amount;\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string sub(buff);
    if(acc.active)
    {
    acc.balance-=stoi(sub);
    setInfo(x,acc);
    string msg= "withdrew "+sub;
    addHistory(x,msg);
    }
    else
    cout<<"acc is deactive"<<endl;
}

void transfer(string &x,int nsd)
{
    account acc1,acc2;
    char buff[1000];
    int bytesRead=0;
    string msg="enter reciever name:\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string y(buff);
    msg="enter amount to transfer:\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string amt(buff);
    getInfo(x,acc1);
    getInfo(y,acc2);
    if((acc1.active)&&(acc2.active))
    {   acc1.balance-=stoi(amt);
        setInfo(x,acc1);    
        acc2.balance+=stoi(amt);
        setInfo(y,acc2);
        string msg = "transfered " + amt +" to " + y;
        addHistory(x,msg);
        msg = "recieved " + amt +" from " + x;
        addHistory(y,msg);
    }
    else if(!acc1.active)
    cout<<"acc "<<x<<" is deactive"<<endl;
    else if(!acc2.active)
    cout<<"acc "<<y<<" is deactive"<<endl;
}

void applyLoan(string &name,int nsd)
{
    char path[256];
    char buff[1000];
    int bytesRead=0;
    string msg="enter amount;\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string amount(buff);
    string dateTime = getCurrentDateTime();
    name = name + "_" + dateTime;
    snprintf(path, sizeof(path), "./loans/unassigned/%s", name.c_str());

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Create if not exists, write permissions
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    char amtBuff[256];
    snprintf(amtBuff, sizeof(amtBuff), "%s", amount.c_str());
    int bytes = write(fd, amtBuff, strlen(amtBuff));
    if (bytes < 0) {
        cerr << "Error writing to file." << endl;
    };

}

void changePasswd(string &path,int nsd)
    {
        account acc;
        getInfo(path,acc);
        char buff[1000];
        int bytesRead=0;
        string msg="enter new password\n";
        write(nsd,msg.c_str(),msg.size());
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        string newPassword(buff);
        acc.passwd = newPassword;
        setInfo(path,acc);
    }

void addFeedBack(int nsd) {

    string filename = "./feedback/feedback.txt";
    int fd = open(filename.c_str(), O_WRONLY | O_APPEND);
    if (fd < 0) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    char buff[1000];
        int bytesRead=0;
        string msg="enter feedback\n";
        write(nsd,msg.c_str(),msg.size());
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        string line(buff);
    line.append("\n");

    off_t offset = lseek(fd, 0, SEEK_END);
    if (offset == (off_t)-1) {
        cerr << "Error seeking to the end of the file." << endl;
        close(fd);
    }


    int bytes = write(fd, line.c_str(), line.size());
    if (bytes < 0) {
        cerr << "Error writing to file." << endl;
    } else {
        cout << "Successfully wrote " << line << " bytes to the file." << endl;
    }

    close(fd);
}


void fullHistory(string &name,int nsd) {
    string path = "./history/" + name;
    int fd = open(path.c_str(), O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        const char* errorMsg = "Error opening file\n";
        write(nsd, errorMsg, strlen(errorMsg)); // Send error message
        return;
    }

    char buffer[1024];
    int lineCount = 0;
    string line;

    while (true) {
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            perror("Error reading file");
            const char* errorMsg = "Error reading file\n";
            write(nsd, errorMsg, strlen(errorMsg)); // Send error message
            close(fd);
            return;
        }
        if (bytesRead == 0) break; // End of file

        buffer[bytesRead] = '\0'; // Null-terminate the buffer

        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] == '\n') {
                // Send the line to the client
                line += '\n'; // Append the newline character for the client
                write(nsd, line.c_str(), line.length()); // Send line
                line.clear(); // Clear the current line
                lineCount++;

                if (lineCount == 10) {
                    const char* prompt = "Press Enter to continue...\n";
                    write(nsd, prompt, strlen(prompt)); // Send prompt

                    // Wait for the client to acknowledge
                    char ack[10];
                    read(nsd, ack, sizeof(ack)); // Read acknowledgment
                    lineCount = 0;
                }
            } else {
                line += buffer[i]; 
            }
        }
    }

    // Send any remaining line (if there's no newline at the end of the file)
    if (!line.empty()) {
        line += '\n'; // Append a newline for consistency
        write(nsd, line.c_str(), line.length()); // Send remaining line
    }

    close(fd);
}

void getInfoEmp(string &x,empAccount &acc) 
{
    
    string path = "./empAccounts/" + x;
    //cout<<path;
    int fd = open(path.c_str(),O_RDONLY);
    //cout<<fd;
    //read(fd,&acc,sizeof(account));
    char buff[1024];
    int size=0;
    string line;
    int pos=0;
    while ((size = read(fd, buff, sizeof(buff))) > 0) 
    {    line.append(buff, size);}
    //get password
        pos= line.find("\n");
        //strncpy(acc.passwd, line.c_str(), sizeof(acc.passwd) - 1);
        //acc.passwd[sizeof(acc.passwd) - 1] = '\0';
        acc.passwd=line.substr(0,pos);
        line=line.substr(pos+1);
}

void setInfoEmp(string &x,empAccount &acc)
{
    string path = "./empAccounts/" + x;
    int fd = open(path.c_str(), O_WRONLY | O_TRUNC);
    if (fd < 0) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    
    // Use sprintf to format and append each field
    snprintf(buff, 1024, "%s", acc.passwd.c_str());

    int bytes = write(fd, buff, strlen(buff));
    if (bytes < 0) {
        std::cerr << "Error writing to file." << std::endl;
    } 

    close(fd);
}

void createCustomer(int nsd){
    char buff[1000];
    int bytesRead = 0;
    string msg="enter customer name:\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string name(buff);
    string path="./customerAccounts/" + name;

    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666); 
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    msg="enter password for customer:\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string passwd(buff);
    char passBuff[256];
    snprintf(passBuff, sizeof(passBuff), "%s\n0\n1", passwd.c_str());
    int bytes = write(fd, passBuff, strlen(passBuff));
    if (bytes < 0) {
        std::cerr << "Error writing to file." << std::endl;
    };
    close(fd);
    path="./history/"+name;
    fd = open(path.c_str(),O_CREAT | O_RDONLY, 0666);
    close(fd);
}

void modifyCustomer(int nsd)
    {
        account acc;
        string name;
        int bytesRead=0;
        char buff[1000];
        cout<<"enter username to modify:"<<endl;
        cin>>name;
        string path="./customerAccounts/"+name;
        getInfo(name,acc);
        cout<<acc.passwd<<endl<<acc.balance<<endl<<acc.active<<endl;
        
        
        string msg="modify acc password?\n1.yes\n0.no\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        string temp(buff);
        int ans=stoi(temp);
        if(ans)
        {   msg="enter new password\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string pass(buff);
            acc.passwd=pass;
        }

        msg="modify acc balance?\n1.yes\n0.no\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        temp=buff;
        ans=stoi(temp);
        if(ans)
        {
            msg="enter new balance\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string balance(buff);
            acc.balance=stoi(balance);
        }
        msg="modify acc status?\n1.yes\n0.no\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        temp=buff;
        ans=stoi(temp);
        if(ans)
        {
            msg="enter new status\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string act(buff);
            acc.active=stoi(act);
        }
        msg="modify acc username?\n1.yes\n0.no\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        temp=buff;
        ans=stoi(temp);
        if(ans)
        {
            msg="enter new name\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string newName(buff);
            setInfo(newName,acc);
            execl("/bin/rm", "rm", path.c_str(), (char *)NULL);
            setInfo(newName,acc);
        }
        else
        {
            setInfo(name,acc);
        }
    }

void processLoan(string name,int nsd)
{
    
    string path = "./loans/" + name; // Change this to your desired directory
    DIR* dir = opendir(path.c_str());
    
    if (dir == nullptr) {
        cerr << "Could not open directory: " << strerror(errno) << endl;
    }

    struct dirent* entry;
    
    char buff[1024];
    string line;
    int size=0;
    int ans=0;
    string msg;
    int bytesRead=0;

    memset(buff, 0, sizeof(buff));
    while ((entry = readdir(dir)) != nullptr) 
    {
        // Skip the special entries "." and ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
        {
           
            
            string fileName(entry->d_name);
            string filePath = "./loans/" + name + "/" + fileName;
            int fd = open(filePath.c_str(),O_RDONLY);
            
            while ((size = read(fd, buff, sizeof(buff))) > 0) 
            {    
                line.append(buff, size);}
            msg = "customer: " + fileName + "\nloan: " + line + "\napprove?\n(press 1 to approve, 0 to reject)\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string temp(buff);
            ans = stoi(buff);
            if(ans)
            {                
    
                string nameReal = fileName.substr(0,fileName.find('_')); 
                //(underscorePos != std::string::npos) ? str.substr(0, underscorePos) : str;


                //deposit
                account acc;
                getInfo(nameReal,acc);
                acc.balance+=stoi(line);
                setInfo(nameReal,acc);

                //add history
                string msg="loan recieved "+line;
                addHistory(nameReal,msg);
            }
            
            
            pid_t pid = fork();
            if (pid == 0) { // Child process
                execl("/bin/rm", "rm", filePath.c_str(), (char*)nullptr);
                // If execl returns, there was an error
                cerr << "Error executing rm: " << strerror(errno) << endl;
                exit(1); // Exit child process
            } else if (pid < 0) {
                cerr << "Fork failed: " << strerror(errno) << endl;}

            line.clear();
            memset(buff, 0, sizeof(buff));
        }
    }

    closedir(dir);

}

void getHistory(int nsd)
{
    int bytesRead=0;
    char buff[1000];
    string msg = "enter customer name\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string name(buff);
    string path= "./history/" + name;
    int fd = open(path.c_str(), O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        
    }

    char buffer[1024];
    vector<string> lines;

    off_t fileSize = lseek(fd, 0, SEEK_END);
    string currentLine;
    for (off_t pos = fileSize - 1; pos >= 0; --pos) {
        lseek(fd, pos, SEEK_SET);
        bytesRead = read(fd, buffer, 1);
        if (bytesRead < 0) {
            perror("Error reading file");
            close(fd);
            
        }

        // If we hit a newline, store the current line
        if (buffer[0] == '\n') {
            if (!currentLine.empty()) {
                lines.push_back(std::string(currentLine.rbegin(), currentLine.rend()));
                currentLine.clear();
            }
        } else {
            currentLine += buffer[0];
        }

        // Stop if we have found the last 5 lines
        if (lines.size() == 5 && pos < fileSize - 1) break; 
    }

    // If the last line doesn't end with a newline, add it
    if (!currentLine.empty()) {
        lines.push_back(string(currentLine.rbegin(), currentLine.rend()));
    }

    // Close the file
    close(fd);
    msg.clear();
    // Print the last 5 lines
    for(auto i: lines)
    {
        msg = msg + i + "\n";
    }
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    }

void changePasswdEmp(string &name,int nsd)
    {
        empAccount acc;
        getInfoEmp(name,acc);
        int bytesRead=0;
        char buff[1000];
        string msg = "enter new password\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        string pass(buff);
        acc.passwd = pass;
        setInfoEmp(name,acc);
    }

void getInfoManager(string &x,empAccount &acc)
{
    
    string path = "./managerAccounts/" + x;
    //cout<<path;
    int fd = open(path.c_str(),O_RDONLY);
    //cout<<fd;
    //read(fd,&acc,sizeof(account));
    char buff[1024];
    int size=0;
    string line;
    int pos=0;
    while ((size = read(fd, buff, sizeof(buff))) > 0) 
    {    line.append(buff, size);}
    //get password
        pos= line.find("\n");
        //strncpy(acc.passwd, line.c_str(), sizeof(acc.passwd) - 1);
        //acc.passwd[sizeof(acc.passwd) - 1] = '\0';
        acc.passwd=line.substr(0,pos);
        line=line.substr(pos+1);
}

void setInfoManager(string &x,empAccount &acc)
{
    string path = "./managerAccounts/" + x;
    int fd = open(path.c_str(), O_WRONLY | O_TRUNC);
    if (fd < 0) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    
    // Use sprintf to format and append each field
    snprintf(buff, 1024, "%s", acc.passwd.c_str());

    int bytes = write(fd, buff, strlen(buff));
    if (bytes < 0) {
        std::cerr << "Error writing to file." << std::endl;
    } 

    close(fd);
}

void changeActive(int nsd)
{
    
    int bytesRead=0;
    char buff[1000];
    string path = "./customerAccounts/"; // Change this to your desired directory
    string msg = "enter the name of an account to change active status\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string name(buff);
    string filePath=path+name;
    //while(!fileExists(filePath))
    //{
    //    cout<<"enter a valid name"<<endl;
    //    cin>>name;
    // }
    msg="activate or deactivate the account?\n1.activate\n0.deactivate\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string temp(buff);
    int ans=stoi(temp);
    account acc;
    getInfo(name,acc);
    acc.active=ans;
    setInfo(name,acc);

}

bool directoryExists(string &dirPath) {
    struct stat info;
    return (stat(dirPath.c_str(), &info) == 0 && S_ISDIR(info.st_mode));
}

void assignLoan(int nsd)
{
    
    string path = "./loans/unassigned"; // Change this to your desired directory
    DIR* dir = opendir(path.c_str());
    
    if (dir == nullptr) {
        cerr << "Could not open directory: " << strerror(errno) << endl;
    }

    struct dirent* entry;
    
    char buff[1024];
    string line;
    int size=0;
    string ans;

    memset(buff, 0, sizeof(buff));
    while ((entry = readdir(dir)) != nullptr) 
    {
        // Skip the special entries "." and ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
        {
            //cout << "customer: " << entry->d_name << endl;
            
            string fileName(entry->d_name);
            string filePath = "./loans/unassigned/"+ fileName;
            int fd = open(filePath.c_str(),O_RDONLY);
            int bytesRead =0;
            
            while ((size = read(fd, buff, sizeof(buff))) > 0) 
            {    
                line.append(buff, size);}
            string msg="customer: "+fileName+"\nloan: "+line+"\nusername to assign:\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string ans(buff);
            string empPath="./loans/" + ans;
            if(directoryExists(empPath))
            {                
                string filePathOld = path + "/" + fileName;
                string filePathNew = empPath + "/" + fileName;
                pid_t pid = fork();
                if (pid == 0) { // Child process
                execl("/bin/mv", "mv", filePathOld.c_str(), filePathNew.c_str(), (char*)nullptr);
                // If execl returns, there was an error
                cerr << "Error executing mv: " << strerror(errno) << endl;
                exit(1); // Exit child process with an error
                } else if (pid < 0) {
                cerr << "Fork failed: " << strerror(errno) << endl;
                } else {
                // Parent process: wait for the child to finish
                wait(nullptr);
                cout << "File moved to: " << filePathNew << endl;
                }
            } 
            else 
                {
                cerr << "emp does not exist." << endl;
                }
        
        }
    }
    cout<<"no unassigned loans left"<<endl;
    closedir(dir);

}

void getFeedBack(int nsd)
{
    string path = "./feedBack/feedBack";
    int fd = open(path.c_str(), O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
    }

    char buff[1024];
    int lineCount = 0;
    string line;
    int bytesRead =0;

    while (true) {
        ssize_t bytesRead = read(fd, buff, sizeof(buff) - 1);
        if (bytesRead < 0) {
            perror("Error reading file");
            close(fd);
        }
        if (bytesRead == 0) break; // End of file

        buff[bytesRead] = '\0'; // Null-terminate the buffer

        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (buff[i] == '\n') {
                line = line +"\n";
                write(nsd,line.c_str(),line.size());
                    memset(buff, 0, sizeof(buff));
                    bytesRead = read(nsd, buff,sizeof(buff));
                    buff[bytesRead] = '\0';
                line.clear(); // Clear the current line
                lineCount++;

                // Check if we've printed 10 lines
                if (lineCount == 10) {
                    string msg= "Press Enter to continue...\n";
                    write(nsd,msg.c_str(),msg.size());
                    memset(buff, 0, sizeof(buff));
                    bytesRead = read(nsd, buff,sizeof(buff));
                    buff[bytesRead] = '\0';
                    lineCount = 0; // Reset line count
                }
            } else {
                line += buff[i]; // Build the current line
            }
        }
    }

    // Print any remaining line (if there's no newline at the end of the file)
    if (!line.empty()) {
        
                    write(nsd,line.c_str(),line.size());
                    memset(buff, 0, sizeof(buff));
                    bytesRead = read(nsd, buff,sizeof(buff));
                    buff[bytesRead] = '\0';
    }

    close(fd);
}

void changePasswdManager(string &name,int nsd)
    {
        empAccount acc;
        getInfoManager(name,acc);
        int bytesRead=0;
        char buff[1000];
        string msg = "enter new password\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        string pass(buff);
        acc.passwd = pass;
        setInfoManager(name,acc);
    }

void getInfoAdmin(adminAccount &acc)
{
    
    string path = "./admin/admin";
    //cout<<path;
    int fd = open(path.c_str(),O_RDONLY);
    //cout<<fd;
    //read(fd,&acc,sizeof(account));
    char buff[1024];
    int size=0;
    string line;
    int pos=0;
    while ((size = read(fd, buff, sizeof(buff))) > 0) 
    {    line.append(buff, size);}
    //get password
        pos= line.find("\n");
        //strncpy(acc.passwd, line.c_str(), sizeof(acc.passwd) - 1);
        //acc.passwd[sizeof(acc.passwd) - 1] = '\0';
        acc.passwd=line.substr(0,pos);
        line=line.substr(pos+1);
}

void setInfoAdmin(adminAccount &acc)
{
    string path = "./admin/admin"; 
    int fd = open(path.c_str(), O_WRONLY | O_TRUNC);
    if (fd < 0) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    
    // Use sprintf to format and append each field
    snprintf(buff, 1024, "%s", acc.passwd.c_str());

    int bytes = write(fd, buff, strlen(buff));
    if (bytes < 0) {
        cerr << "Error writing to file." << std::endl;
    } 

    close(fd);
}

void modifyEmp(int nsd)
    {
        empAccount acc;
        string name;
        int bytesRead=0;
        char buff[1000];
        cout<<"enter username to modify:"<<endl;
        cin>>name;
        string path="./empAccounts/"+name;
        getInfoEmp(name,acc);
        //cout<<acc.passwd<<endl<<acc.balance<<endl<<acc.active<<endl;
        
        
        string msg="modify acc password?\n1.yes\n0.no\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        string temp(buff);
        int ans=stoi(temp);
        if(ans)
        {   msg="enter new password\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string pass(buff);
            acc.passwd=pass;
        }
        msg="modify acc username?\n1.yes\n0.no\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        temp=buff;
        ans=stoi(temp);
        if(ans)
        {
            msg="enter new name\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string newName(buff);
            setInfoEmp(newName,acc);
            execl("/bin/rm", "rm", path.c_str(), (char *)NULL);
            setInfoEmp(newName,acc);
        }
        else
        {
            setInfoEmp(name,acc);
        }
    }

void manageRole(int nsd) //check
    {
        int bytesRead = 0;
        char buff[1000];
        empAccount acc;
        string name;
        string msg= "enter username to modify:\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        name=buff;
        string path="./empAccounts/"+name;
        string role;
        if(fileExists(path))
        {
            role="emp";
            getInfoEmp(name,acc);

        }
        else{
            path="./managerAccounts/"+name;
            if(fileExists(path))
            {
                role="manager";
                getInfoManager(name,acc);
            }
            else
            {
            cout<<"username not found"<<endl;
            return;
            }
        }
        msg="modify acc password?\n1.yes\n0.no\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        string temp(buff);
        int ans=stoi(temp);
        if(ans)
        {   msg="enter new password:\n";
            write(nsd,msg.c_str(),msg.size());
            memset(buff, 0, sizeof(buff));
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string pass(buff);
            acc.passwd = pass;
        }
        if(role=="manager") setInfoManager(name,acc);
        if(role=="emp") setInfoEmp(name,acc);


       
    }

void createEmp(int nsd){
    char buff[1000];
    int bytesRead = 0;
    string msg="enter customer name:\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string name(buff);
    string path="./customerAccounts/" + name;

    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666); 
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    msg="enter password for customer:\n";
    write(nsd,msg.c_str(),msg.size());
    memset(buff, 0, sizeof(buff));
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string passwd(buff);
    char passBuff[256];
    snprintf(passBuff, sizeof(passBuff), "%s\n0\n1", passwd.c_str());
    int bytes = write(fd, passBuff, strlen(passBuff));
    if (bytes < 0) {
        std::cerr << "Error writing to file." << std::endl;
    };
    close(fd);
    path="./loans/"+name;
    execl("/bin/mkdir", "mkdir", path.c_str(), (char *) nullptr);

}

void changePasswdAdmin(int nsd)
    {
        adminAccount acc;
        getInfoAdmin(acc);
        int bytesRead=0;
        char buff[1000];
        string msg = "enter new password\n";
        write(nsd,msg.c_str(),msg.size());
        memset(buff, 0, sizeof(buff));
        bytesRead = read(nsd, buff,sizeof(buff));
        buff[bytesRead] = '\0';
        string pass(buff);
        acc.passwd = pass;
        setInfoAdmin(acc);
    }

int fileExists(string &path) {
    int fd = open(path.c_str(), O_RDONLY);
    if (fd != -1) {
        close(fd); // Close the file descriptor if the file exists
        return 1;
    }
    return 0;
}


void loginC(int nsd,int i)
{
    if(!i) return; 
    char buff[1000];
    account acc;
    int bytesRead=0;
    string msg="enter username\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string name(buff);
    //name.pop_back();
    memset(buff, 0, sizeof(buff));
    cout<<"name: "<<name<<endl<<"size(): "<<name.size()<<endl;
    string path = "./customerAccounts/" + name;
    cout<<path<<endl;
    if(fileExists(path))
       {   
            msg="enter password\n";
            write(nsd,msg.c_str(),msg.size());
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string password(buff);
            //password;
            memset(buff, 0, sizeof(buff));
            
            
            getInfo(name,acc);

            //cout<<acc.passwd<<" s: "<<acc.passwd.size()<<endl<<password<<" s: "<<password.size()<<endl;
            if(acc.passwd==password)
            {
                customerHandler(name,nsd);
            }
       }
    else
        {
            msg="incorrect username re-enter\n";
            loginC(nsd,--i);

        }
   
}

void loginE(int nsd,int i)
{
    if(!i) return; 
    char buff[1000];
    empAccount acc;
    int bytesRead=0;
    string msg="enter username\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string name(buff);
    //name.pop_back();
    memset(buff, 0, sizeof(buff));
    cout<<"name: "<<name<<endl<<"size(): "<<name.size()<<endl;
    string path = "./empAccounts/" + name;
    cout<<path<<endl;
    if(fileExists(path))
       {   
            msg="enter password\n";
            write(nsd,msg.c_str(),msg.size());
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string password(buff);
            //password;
            memset(buff, 0, sizeof(buff));
            getInfoEmp(name,acc);
            cout<<acc.passwd<<" s: "<<acc.passwd.size()<<endl<<password<<" s: "<<password.size()<<endl;
            if(acc.passwd==password)
            {
                employeeHandler(name,nsd);
            }
       }
    else
        {
            msg="incorrect username re-enter\n";
            loginE(nsd,--i);

        }
   
}

void loginM(int nsd,int i)
{
    if(!i) return; 
    char buff[1000];
    empAccount acc;
    int bytesRead=0;
    string msg="enter username\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    string name(buff);
    //name.pop_back();
    memset(buff, 0, sizeof(buff));
    cout<<"name: "<<name<<endl<<"size(): "<<name.size()<<endl;
    string path = "./managerAccounts/" + name;
    cout<<path<<endl;
    if(fileExists(path))
       {   
            msg="enter password\n";
            write(nsd,msg.c_str(),msg.size());
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string password(buff);
            //password;
            memset(buff, 0, sizeof(buff));
            getInfoManager(name,acc);
            cout<<acc.passwd<<" s: "<<acc.passwd.size()<<endl<<password<<" s: "<<password.size()<<endl;
            if(acc.passwd==password)
            {
                managerHandler(name,nsd);
            }
       }
    else
        {
            msg="incorrect username re-enter\n";
            loginM(nsd,--i);

        }
   
}

void loginA(int nsd,int i)
{
    if(!i) return; 
    char buff[1000];
    adminAccount acc;
    int bytesRead=0;
    string msg;
    string path = "./admin/admin";
    cout<<path<<endl;
    if(fileExists(path))
       {   
            string name;
            msg="enter password\n";
            write(nsd,msg.c_str(),msg.size());
            bytesRead = read(nsd, buff,sizeof(buff));
            buff[bytesRead] = '\0';
            string password(buff);
            //password;
            memset(buff, 0, sizeof(buff));
            getInfoAdmin(acc);
            cout<<acc.passwd<<" s: "<<acc.passwd.size()<<endl<<password<<" s: "<<password.size()<<endl;
            if(acc.passwd==password)
            {
                name="admin";
                adminHandler(name,nsd);
            }
       }
    else
        {
            msg="incorrect username re-enter\n";
            loginA(nsd,--i);

        }
   
}

void customerHandler(string name,int nsd) //check
{
    int bytesRead=0;
    char buff[1000];
    int choice;
    do{
    string msg="\n1.get balance\n2.deposit money\n3.withdraw money\n4.transfer funds\n5.apply loan\n6.change password\n7.adding feedback\n8.view transaction history\n9.logout\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    choice = stoi(buff);
    switch (choice)
            {
            case 1:
                
                getBalance(name,nsd);
                break;
            case 2:
                
                deposit(name,nsd);
                break;
            case 3:
                // manager
                withdraw(name,nsd);
                break;
            case 4:
                transfer(name,nsd);
                break;
            case 5:
                applyLoan(name,nsd);
                break;
            case 6:
                changePasswd(name,nsd);
                break;
            case 7:
                addFeedBack(nsd);
                break;
            case 8:
                fullHistory(name,nsd);
                break;
            case 9:
                //logout
                break;
            default:
                // Exit
                break;
            }
    }while(choice!=9);

}

void employeeHandler(string name,int nsd)
{
    int bytesRead=0;
    char buff[1000];
    int choice;
    do{
    string msg="\n1.add new customer\n2.modify customer\n3.process loans\n4.view customer transactions\n5.change password\n6.logout\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    choice = stoi(buff);
    switch (choice)//check
            {
            case 1:
                
                createCustomer(nsd);
                break;
            case 2:
                
                modifyCustomer(nsd);
                break;
            case 3:
                // manager
                processLoan(name,nsd);
                break;
            case 4:
                getHistory(nsd);
                break;
            case 5:
                changePasswdEmp(name,nsd);
                break;
            case 6:
                //logout
                break;
            default:
                // Exit
                break;
            }
    }while(choice!=6);

}

void managerHandler(string name, int nsd)
{
    int bytesRead=0;
    char buff[1000];
    int choice;
    do{
    string msg="\n1.activate/deactivate accounts\n2.assign loan to emp\n3.review feedback\n4.change password\n5.logout\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    choice = stoi(buff);
    switch (choice)//check
            {
            case 1:
                
                changeActive(nsd);
                break;
            case 2:
                
                assignLoan(nsd);
                break;
            case 3:
                // manager
                getFeedBack(nsd);
                break;
            case 4:
                changePasswdManager(name,nsd);
                break;
            case 5:
                //logout
                break;
            default:
                // Exit
                break;
            }
    }while(choice!=5);
}

void adminHandler(string name, int nsd)
{
    int bytesRead=0;
    char buff[1000];
    int choice;
    do{
    string msg="\n1.add new employee\n2.modify customer\n3.modify employee\n4.manage user roles\n5.change password\n6.logout\n";
    write(nsd,msg.c_str(),msg.size());
    bytesRead = read(nsd, buff,sizeof(buff));
    buff[bytesRead] = '\0';
    choice = stoi(buff);
    switch (choice)//check
            {
            case 1:
                
                createEmp(nsd);
                break;
            case 2:
                
                modifyCustomer(nsd);
                break;
            case 3:
                // manager
                modifyEmp(nsd);
                break;
            case 4:
                manageRole(nsd);
                break;
            case 5:
                changePasswdEmp(name,nsd);
                break;
            case 6:
                //logout
                break;
            default:
                // Exit
                break;
            }
    }while(choice!=6);
}

void connectionHandler(int nsd)
{   
    int choice;
    char buff[1000];
    do{
    memset(buff, 0, sizeof(buff));
    string msg="choose user type:\n1.customer\n2.employee\n3.manager\n4.admin\n5.EXIT";
    write(nsd,msg.c_str(),msg.size());

    read(nsd, buff,size(buff));
    choice = atoi(buff);
    cout<<choice<<endl;
            switch (choice)
            {
            case 1:
                // customer
                loginC(nsd,3);
                break;
            case 2:
                // employee
                loginE(nsd,3);
                break;
            case 3:
                // manager
                loginM(nsd,3);
                break;
            case 4:
                // admin
                loginA(nsd,3);
                break;
            case 5:
                break;
            default:
                // Exit
                break;
            }
    }while(choice!=5);
}

int main() {
    struct sockaddr_in serv, cli;
    int sd, nsd;
    char buf[80];

    // Create a socket descriptor
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Specify the type of socket
    serv.sin_family = AF_INET;  // Use AF_INET for IPv4
    serv.sin_addr.s_addr = htonl(INADDR_ANY);  // Automatically assign IP address
    serv.sin_port = htons(8081);  // Port number

    // Bind the socket to the specified address and port
    if (bind(sd, (struct sockaddr*)(&serv), sizeof(serv)) < 0) {
        perror("Bind failed");
        close(sd);
        return 1;
    }

    // Start listening for connections
    listen(sd, 5); // 5 = size of wait queue for connections
    int sz = sizeof(cli);

    // Accept connection from client
    nsd = accept(sd, (struct sockaddr*)(&cli), (socklen_t*)&sz);
    if (nsd < 0) {
        perror("Accept failed");
        close(sd);
        return 1;
    }

    //##############################
    connectionHandler(nsd);

    close(nsd);
    close(sd);
    return 0;
}



