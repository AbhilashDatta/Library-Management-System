#include<iostream>
#include<dirent.h>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<sstream>
#include<fstream>
#include<set>
using namespace std;

class Book{
public:
    string filename, title, author,
    type, release_date, language, path;

    Book(){}
    Book(string filename_,string title_,string author_):filename(filename_),title(title_),author(author_){}
    ~Book(){}

    void display() const{
        cout<<"FILENAME: "<<filename<<endl;
        cout<<"TITLE: "<<title<<endl;
        cout<<"AUTHOR: "<<author<<endl;
        cout<<"RELEASE DATE: "<<release_date<<endl;
        cout<<"LANGUAGE: "<<language<<endl;
        cout<<"TYPE: "<<type<<endl;
    }
    void scan_book(){
        fstream file;
        file.open(path,ios::in);
        string word,line;
        while(word!="***"){
            file>>word;
            if(word=="Title:"){
                getline(file,line);
                line = line.substr(line.find(':')+2);
                title = line;
            }
            if(word == "Author:"){
                getline(file, line);
                line = line.substr(line.find(':')+2);
                author = line;
            }
            if(word == "Release"){
                getline(file, line);
                line = line.substr(line.find(':')+2,line.find('[')-7);
                release_date = line;
            }
            if(word == "Language:"){
                getline(file, line);
                line = line.substr(line.find(':')+2);
                language = line;
            }
        }
        file.close();
    }
};

class Novel: public Book{
public:
    Novel(Book book){
        title = book.title;
        author = book.author;
        path = book.path;
        language = book.language;
        release_date = book.release_date;
    }
    ~Novel(){}

    void display_para_n(int n) const{
        fstream file;
        //cout<<title<<endl;
        file.open(path,ios::in);
        string line;
        int para_count = 0;
        int flag = 0;
        while(getline(file,line)){
            //cout<<"Line size: " <<line.size()<<endl;
            if(line.size()<=1 && flag==0){
                para_count++;
                //cout<<para_count<<endl;
                flag = 1;
                continue;
            }
            else if(line.size()>1){
                flag = 0;
            }
            if(para_count==n){
                cout<<line<<endl;
                continue;
            }
            if(para_count>n) break;
        }
        file.close();
        return;
    }

    void display_paragraphs(int k = 5) const{
        cout<<"Enter the required word: ";
        string word;
        cin>>word;
        transform(word.begin(),word.end(),word.begin(),::tolower);
        cout<<"Enter the value of k: ";
        cin>>k;
        cout<<"\nThe top "<<k<<" paragraphs with '"<<word<<"' are as follows:-\n";
        vector<int> words_per_para;
        fstream file;
        string line,s;
        file.open(path,ios::in);
        int count = 0;
        int flag = 1;
        while(getline(file,line)){
            if(line.size()>1){
                transform(line.begin(),line.end(),line.begin(),::tolower);
                stringstream sstr(line);
                string w;
                while(sstr>>w){
                    if(w[w.size()-1]=='.' || w[w.size()-1]==',' || w[w.size()-1]==';' || w[w.size()-1]=='!' || w[w.size()-1]=='-'){
                    //if(w[w.size()-1]>='!' && w[w.size()-1]<='@'){ 
                        w = w.substr(0,w.size()-1);
                        //cout<<w<<endl;
                    }
                    if(w.compare(word)==0) count++;
                }
                flag = 1;
            }
            else if(line.size()<=1 && flag==1){
                words_per_para.push_back(count);
                //cout<<count<<endl;
                count = 0;
                flag = 0;
            }
        }
        for(int i=0;i<k;i++){
            if(*max_element(words_per_para.begin(),words_per_para.end())==0){
                cout<<"\nSEARCH EXHAUSTED"<<endl;
                break;
            }
            cout<<"\nParagraph "<<i+1<<":\n"<<endl;
            display_para_n(max_element(words_per_para.begin(),words_per_para.end())-words_per_para.begin());
            cout<<"\nCOUNT: "<<*max_element(words_per_para.begin(),words_per_para.end())<<endl;
            words_per_para[max_element(words_per_para.begin(),words_per_para.end())-words_per_para.begin()] = -1;
        }
        file.close();
    }

    void display_chapters(int k = 5) const{
        cout<<"Enter the required word: ";
        string word;
        cin>>word;
        //word = " "+word;
        cout<<"Enter the value of k: ";
        cin>>k;
        cout<<"\nThe top "<<k<<" chapters with '"<<word<<"' are as follows:-\n"<<endl;
        vector<int> words_per_chapter;
        map<int,string> chapter;
        fstream file;
        string line,s;
        file.open(path,ios::in);
        transform(word.begin(),word.end(),word.begin(),::tolower);
        int count = 0;
        int num = 0;
        while(getline(file,line)){
            if(line.find("CHAPTER")==0){
                int pos = line.find('.');
                chapter[++num] = line.substr(pos+2);
                words_per_chapter.push_back(count);
                count = 0;
            }
            /*if(line.find('.')!=string::npos && title=="Heretics"){
                string t = line.substr(0,line.find('.'));
                string z = t;
                transform(t.begin(),t.end(),t.begin(),::toupper);
                if(z.find(t)==0){
                    int pos = line.find('.')-1;
                    chapter[++num] = line.substr(pos+2);
                    words_per_chapter.push_back(count);
                    count = 0;
                }
            }*/
            if(line.size()>1){
                transform(line.begin(),line.end(),line.begin(),::tolower);
                stringstream sstr(line);
                string w;
                while(sstr>>w){
                    if(w[w.size()-1]=='.' || w[w.size()-1]==',' || w[w.size()-1]==';' || w[w.size()-1]=='!' || w[w.size()-1]=='-'){
                        w = w.substr(0,w.size()-1);
                        //cout<<w<<endl;
                    }
                    if(w.compare(word)==0) count++;
                }
            }
        }
        words_per_chapter.push_back(count);
        for(int i=0;i<k;i++){
            int index = max_element(words_per_chapter.begin(),words_per_chapter.end())-words_per_chapter.begin();
            if(index==0){
                cout<<"\nSEARCH EXHAUSTED"<<endl;
                break;
            }
            cout<<"CHAPTER "<<index<<": "<<chapter[index]<<endl;
            words_per_chapter[index] = -1;
        }
        file.close();
    }
};

class Play: public Book{
public:
    Play(Book book){
        title = book.title;
        author = book.author;
        path = book.path;
        language = book.language;
        release_date = book.release_date;
    }

    ~Play(){}

    void display_characters() const{
        fstream file;
        file.open(path,ios::in);
        vector<set<string>> Characters_per_scene;
        set<string> Character;

        string line;
        int scene = 0;
        int flag = 0;
        while(getline(file,line)){
            //if(line.size()==1) continue;
            if(line.find("SCENE")!= string::npos){
                scene++;
                if(flag){
                    Characters_per_scene.push_back(Character);
                }
                flag = 1;
                Character.clear();
            }
            else if(line.size()>1 && line.find("ACT")!=0 && line.find("***")!=0 && line.find("ALL")!=0 && line.find("BOTH")!=0 && line.find("CHORUS")!=0){
                line = line.substr(0,line.find('.'));
                //cout<<line<<endl;
                string temp = line;
                transform(temp.begin(),temp.end(),temp.begin(),::toupper);
                //cout<<temp<<endl;
                if(line.find(temp)==0) Character.insert(line);
            }
            else continue;
        }
        cout<<"\nLIST OF ALL CHARACTERS IN THE PLAY:\n"<<endl;
        int x = 0,y = 0;
        for(auto& c:Characters_per_scene){
            for(auto& i:c){
                Character.insert(i);
            }
        }   
        for(auto& i:Character){
            cout<<++x<<": "<<i<<endl;
        }
        file.close();
        int id;
        char ans = 'Y';
        while(toupper(ans)!='N'){
            cout<<"\nEnter Character ID: ";
            cin>>id;
            set<string>::iterator it = Character.begin();
            advance(it,id-1);
            string character = *it;
            set<string> s; 
            for(auto& c:Characters_per_scene){
                if(find(c.begin(),c.end(),character)!=c.end()){
                    for(auto& i:c){
                        if(i!=character) s.insert(i); 
                    }
                }
            } 
            cout<<"\nCharacters along with "<<character<<" in the play are: \n"<<endl;
            for(auto& i:s){
                cout<<"- "<<i<<endl;
            }
            cout<<"\nWant to search for another character? (Y/N): ";
            cin>>ans;
        }
        return;
    }
};

void print_menu(){
    cout<<"\n=====================================MENU========================================\n";
    cout<<"Enter (1) to LIST all books in the Library.\n";
    cout<<"Enter (2) to SEARCH for a book in the Library.\n";
    cout<<"Enter (3) to DISPLAY top k paragraphs/chapters with a word in it within a Novel.\n";
    cout<<"Enter (4) to LIST all characters that were with a character in any scene.\n";
    cout<<"Enter (5) to QUIT.\n";
    cout<<"=================================================================================\n";
    return ;
}

vector<string> list_books(const char* path) {
    struct dirent *entry;
    DIR *directory = opendir(path);
    vector<string> files;

    if (!directory) return files;
    while (entry = readdir(directory))
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) files.push_back(entry->d_name);

    closedir(directory);
    return files;
}

void update_index(vector<string>& new_files, vector<string>& new_filenames, vector<string>& new_types){
    vector<string> old_filenames,old_types;
    fstream file;
    file.open("index.txt",ios::in);
    string text;
    while (file>>text){
        old_filenames.push_back(text);
        file>>text;
        old_types.push_back(text);
    }
    file.close();
    file.open("index.txt",ios::out);
    string type;
    for (int i=0;i<new_files.size();i++){
        if(find(old_filenames.begin(),old_filenames.end(),new_files[i])==old_filenames.end()){
            cout<<"New Book Found: "<<new_files[i]<<endl;
            cout<<"Enter type: ";
            cin>>type;
        }
        else{
            type = old_types[find(old_filenames.begin(),old_filenames.end(),new_files[i])-old_filenames.begin()];
        }
        new_filenames.push_back(new_files[i]);
        new_types.push_back(type);
        file<<new_filenames[i]<<"\t"<<type<<endl;
    }
    file.close();
    return;
}

vector<Book> make_books(vector<string> new_filenames,vector<string> new_types, string directory){
    vector<Book> books;
    for(int i=0;i<new_filenames.size();i++){
        Book temp;
        temp.type = new_types[i];
        temp.filename = new_filenames[i];
        temp.path = directory + "/" + new_filenames[i];
        temp.scan_book();
        books.push_back(temp);
    }
    return books;
}

void List_books(const vector<Book>& books){
    cout<<"\nLIST OF BOOKS\n"<<endl;
    for(int i=0;i<books.size();i++){
        cout<<"BOOK ID: "<<i+1<<endl;
        cout<<"FILENAME: "<<books[i].filename<<endl;
        cout<<"TITLE: "<<books[i].title<<endl;
        cout<<"AUTHOR NAME: "<<books[i].author<<endl; 
        cout<<endl;       
    }
}

void display_book(const Book& book){
    fstream file;
    file.open(book.path,ios::in);
    string line;
    char input = 'y';
    while(toupper(input)!='N'){
        for(int i=0;i<50;i++){
            getline(file,line);
            cout<<line<<endl;
            if(line.size()<=1) i--;
        }
        cout<<"\nDo you want to continue reading? (Y/N): ";
        cin>>input;
    }
}

void search_book(const vector<Book>& books){
    cout<<"\nBOOK SEARCH\n\n";
    cout<<"Enter (1) to search using TITLE\nEnter (2) to search using AUTHOR\n";
    int input;
    cout<<"Enter Response: ";
    cin>>input;
    vector<Book> results;
    if(input==1){
        string title;
        cout<<"Enter Title: ";
        getchar();
        getline(cin,title);
        transform(title.begin(), title.end(), title.begin(), ::toupper);
        int flag = 0;
        for (int i=0;i<books.size();i++){
            string temp = books[i].title;
            transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
            if(temp.find(title)!= string::npos){
                cout<<"\nBOOK ID:"<<i+1<<endl;
                books[i].display();
                results.push_back(books[i]);
                flag = 1;
            }
        } 
        if(flag==0){
            cout<<"\nNO RESULTS FOUND\n";
        }
    }
    if(input==2){
        string author;
        cout<<"Enter Author: ";
        getchar();
        getline(cin,author);
        transform(author.begin(), author.end(), author.begin(), ::toupper);

        for (int i=0;i<books.size();i++){
            string temp = books[i].author;
            transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
            if(temp.find(author)!=string::npos){
                cout<<"\nBOOK ID: "<<i+1<<endl;
                books[i].display();
                results.push_back(books[i]);
            }
        } 
    }
    if(input!=1 && input!=2){
        cout<<"Invalid Response\n";
    }
    return;
}

void search_word(const vector<Novel>& novels){
    cout<<"\nNOVELS LIST"<<endl;
    for(int i=0;i<novels.size();i++){
        cout<<"\nNOVEL ID: "<<i+1<<endl;
        cout<<"TITLE: "<<novels[i].title<<endl;
        cout<<"AUTHOR: "<<novels[i].author<<endl;
        cout<<"LANGUAGE: "<<novels[i].language<<endl;
        cout<<"RELEASE DATE: "<<novels[i].release_date<<endl;
    }
    int id;
    char resp = 'Y';
    while(toupper(resp)!='N'){
        cout<<"\nEnter NOVEL ID: ";
        cin>>id;
        cout<<"\nEnter (1) to display paragraphs\nEnter (2) to display chapters\n";
        int input;
        cout<<"Enter Response: ";
        cin>>input;
        if(input==1) novels[id-1].display_paragraphs();
        else if(input==2) novels[id-1].display_chapters();
        else cout<<"Invalid Input\n";
        cout<<"\nWant to search another word? (Y/N): ";
        cin>>resp;
    }
    return;
}

void search_character(const vector<Play>& plays){
    cout<<"\nPLAYS LIST"<<endl;
    for(int i=0;i<plays.size();i++){
        cout<<"\nPLAY ID: "<<i+1<<endl;
        cout<<"TITLE: "<<plays[i].title<<endl;
        cout<<"AUTHOR: "<<plays[i].author<<endl;
        cout<<"LANGUAGE: "<<plays[i].language<<endl;
        cout<<"RELEASE DATE: "<<plays[i].release_date<<endl;
    }
    int id;
    cout<<"\nEnter PLAY ID: ";
    cin>>id;
    plays[id-1].display_characters();
    return;
}


int main(int argc, char* argv[]){
    const char* directory = argv[1];
    vector<string> files = list_books(directory);
    //for(auto& i:files) cout<<i<<endl;

    vector<string> new_filenames,new_types;

    update_index(files,new_filenames,new_types);
    vector<Book> Book_list = make_books(new_filenames,new_types,directory);
    
    vector<Novel> Novel_list;
    for(auto& book:Book_list){
        if(book.type=="novel"){
            Novel n = Novel(book);
            Novel_list.push_back(n);
        }
    }
    
    vector<Play> Play_list;
    for(auto& book:Book_list){
        if(book.type=="play"){
            Play p = Play(book);
            Play_list.push_back(p);
        }
    }
    
    cout<<"\n\n----------------------------:WELCOME TO THE LIBRARY:----------------------------\n\n";    
    
    int response = 0;
    while(response!=5){
    try{
        print_menu();
        cout<<"\nEnter Response: ";
        cin>>response;
        if(response==1){
            List_books(Book_list);
            char input;
            int id;
            cout<<"Want to see any book? (Y/N): ";
            cin>>input;
            while(toupper(input)!='N'){
                cout<<"Enter Book ID: ";
                cin>>id;
                cout<<"\nLOADING...\n\n";
                display_book(Book_list[id-1]);
                cout<<"Want to see another book? (Y/N): ";
                cin>>input;
            }
        }
        if(response==2){
            char x = 'y';
            while(toupper(x)!='N'){
                search_book(Book_list);
                char input;
                int id;
                cout<<"\nWant to see any book? (Y/N): ";
                cin>>input;
                while(toupper(input)!='N'){
                    cout<<"Enter Book ID: ";
                    cin>>id;
                    display_book(Book_list[id-1]);
                    cout<<"Want to see another book? (Y/N): ";
                    cin>>input;
                }
                cout<<"\nWant to search another Book? (Y/N): ";
                cin>>x;
            }
        }
        if(response==3){
            search_word(Novel_list);
        }
        if(response==4){
            search_character(Play_list);
        }
        
        //cout<<"Enter Response: ";
        //cin>>response;
        if(response>5 || response<1){
            throw ("error");
        }
        }
        catch(...){
            cout<<"INVALID RESPONSE\n"<<endl;
            continue;
        }
    }
    return 0;    
}