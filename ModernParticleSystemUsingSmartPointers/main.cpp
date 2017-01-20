#include <iostream>
#include <memory>
#include <vector>

/*
 * This class shows how 2 vector containers could be "synchronized".
 * Practically, the monitoredPool vector of shared_ptr is monitored
 * by referencesToPool.
 * When an index is about to be removed from monitoredPool, then we save this index and
 * "update/remove" the corresponding index from referencesToPool too.
*/

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
     std::vector<std::shared_ptr<Particle>> monitoredPool;
     monitoredPool.reserve(5);//save invalidation of referencesToPool because of reallocation on monitoredPool vector

     // pointer to particle pointer..or the address of a particle pointer in the container
     //
     std::vector<std::shared_ptr<Particle>> referencesToPool;
     referencesToPool.resize(5);


     for (int i=0; i<5; ++i)
     {
       std::unique_ptr<Particle> a(new Particle(i));
       monitoredPool.push_back(std::move(a));

       referencesToPool[i]=monitoredPool[i];

     }


     //save a list with removed indices to use and remove elements in referencesToPool
     std::vector<int>indexToRemovedFromreferenesToPoolVector;

     //Calculate which element to delete
     int saveRemoveIndex=2;

     //DELETE THE 3rd ELEMENT FROM ORIGINAL VECTOR
     std::vector<std::shared_ptr<Particle>>::iterator it; it=monitoredPool.begin();
     monitoredPool.erase(it+saveRemoveIndex);
     indexToRemovedFromreferenesToPoolVector.push_back(saveRemoveIndex);


     //UPDATE VECTOR "reference to original" vector based on saved "indices to be removed"

     std::vector<std::shared_ptr<Particle>>::iterator it2; it2=referencesToPool.begin();
     for(const auto &el:indexToRemovedFromreferenesToPoolVector)
     {
        referencesToPool.erase(it2+el);
     }



    return 0;
}

