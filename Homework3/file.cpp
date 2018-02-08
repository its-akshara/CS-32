//#include <iostream>
//#include <string>
//using namespace std;

class File{
    string m_name;
    
public:
    File(string name)
    {
        m_name = name;
    }
     string name() const {
        return m_name;
    }
     virtual void open() const
    {
        
    }
     virtual void redisplay() const
    {
        cout<<"refresh the screen";
    }
    virtual ~File()
    {
        
    }
};
class TextMsg:public File{
    
public:
    TextMsg(string name): File(name){
        
    }
    virtual void open() const
    {
        cout<<"open text message";
    }
    virtual ~TextMsg()
    {
        cout<<"Destroying "<<name()<<", a text message"<<endl;
    }
};
class Video:public File{
    int m_time;
public:
    Video(string name, int time):File(name)
    {
        m_time = time;
    }
    virtual void redisplay() const
    {
        cout<<"replay video";
    }
    virtual void open() const
    {
        cout<<"play "<<m_time<<" second video";
    }
    virtual ~Video()
    {
        cout<<"Destroying "<<name()<<", a video"<<endl;
    }
    
};
class Picture:public File{
    
public:
    Picture(string name): File(name){
        
    }
    virtual ~Picture()
    {
        cout<<"Destroying the picture "<<name()<<endl;;
    }
    virtual void open() const
    {
        cout<<"show picture";
    }
};
/*
void openAndRedisplay(const File* f)
{
    cout << f->name() << ": ";
    f->open();
    cout << endl << "Redisplay: ";
    f->redisplay();
    cout << endl;
}

int main()
{
   
  
    
    File* files[4];
    files[0] = new TextMsg("fromFred.txt");
    // Videos have a name and running time
    files[1] = new Video("goblin.mpg", 3780);
    files[2] = new Picture("kitten.jpg");
    files[3] = new Picture("baby.jpg");
    
    for (int k = 0; k < 4; k++)
        openAndRedisplay(files[k]);
    
    // Clean up the files before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete files[k];

}*/
