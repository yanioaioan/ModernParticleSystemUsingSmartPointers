#include <iostream>
#include <memory>
#include <vector>


class Particle
{
    public:
        int id;

        Particle(int _id)
    //        : cstring(new char[std::strlen(arg)+1]) // allocate
            {
    //            std::strcpy(cstring, arg); // populate
                id=_id;
            }
            ~Particle()
            {
    //            delete[] cstring;  // deallocate
            }
            Particle(const Particle& other) // copy constructor
            {
    //            cstring = new char[std::strlen(other.cstring) + 1];
    //            std::strcpy(cstring, other.cstring);
            }
            Particle& operator=(const Particle& other) // copy assignment
            {
    //            char* tmp_cstring = new char[std::strlen(other.cstring) + 1];
    //            std::strcpy(tmp_cstring, other.cstring);
    //            delete[] cstring;
    //            cstring = tmp_cstring;
    //            return *this;
            }
};



int main(int argc, char *argv[])
{
    std::vector<std::unique_ptr<Particle> > vectorOfParticles;

    for(int i =0;i<10;i++)
    {
        std::unique_ptr<Particle> p (new Particle(i));
        vectorOfParticles.push_back(std::move(p));
    }






    std::cout << "Hello World!" << std::endl;
    return 0;
}

