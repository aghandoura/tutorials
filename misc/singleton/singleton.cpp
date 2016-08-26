#include <cstddef>
#include <iostream>
#include <mutex>

static int test = 5;
class singleton{
    public:
        static singleton* get_instance(){
            std::cout <<"getting instace "<<std::endl;
            if(m_instance == NULL){
                std::mutex my_mutex;
                my_mutex.lock();
                    if(m_instance == NULL){
                        m_instance = new singleton;
                    }
                my_mutex.unlock();
            }

            return m_instance;
        }
        void kill(){

            if(m_instance){
                std::mutex my_mutex;
                my_mutex.lock();
                    if(m_instance){
                      std::cout <<"killing "<<std::endl;
                      delete m_instance;
                      m_instance =NULL;
                    }
                my_mutex.unlock();
            }

        }
    private:
        singleton(){std::cout << "object created"<<std::endl;}
        ~singleton(){std::cout << "object destroyed"<<std::endl;}
        static singleton *m_instance;
        singleton& operator=(singleton& other);
};



singleton* singleton::m_instance = NULL;


#include <linux/config.h>

int main(int argc, char** argv){


    int test= 50;
    singleton* lonesom_man;
    lonesom_man = singleton::get_instance();


    std::cout <<"---------------------------"<<test<<std::endl;
    std::cout <<(int*)lonesom_man<<std::endl;

    singleton* lonesom_man2;
    lonesom_man2 = singleton::get_instance();
    std::cout <<(int*)lonesom_man2<<std::endl;

    singleton* lonesom_man3;
    lonesom_man3 = singleton::get_instance();
    std::cout <<(int*)lonesom_man3<<std::endl;

    lonesom_man->kill();
    lonesom_man2->kill();
    lonesom_man3->kill();

}


