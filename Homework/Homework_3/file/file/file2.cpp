//
//  file.cpp
//  file
//
//  Created by Runjia Li on 2/8/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//


#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here
class File
{
public:
    File(string name): m_name(name) {}
    string name() const {return m_name;}
    virtual void open() const =0;
    virtual void redisplay() const {cout << "refresh the screen";}
    virtual ~File() {}
private:
    string m_name;
};


class TextMsg: public File
{
public:
    TextMsg(string name): File(name) {}
    virtual void open() const {cout << "open text message";}
    virtual ~TextMsg() {cout << "Destroying " << File::name() << ", a text message" << endl;}
};


class Video: public File
{
public:
    Video(string name, int size): File(name), m_size(size) {}
    virtual void open() const {cout<< "play " << m_size << " second video";}
    virtual void redisplay() const {cout << "replay video";}
    virtual ~Video() {cout << "Destroying " << File::name() << ", a video" << endl;}
private:
    int m_size;
};


class Picture: public File
{
public:
    Picture(string name): File(name) {}
    virtual void open() const {cout << "show picture";}
    virtual ~Picture() {cout << "Destroying the picture " << File::name() << endl;}
};


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

    cout << "After a series of 322s, now its time to make my comeback." << endl;

}
