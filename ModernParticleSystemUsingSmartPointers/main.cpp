#include <iostream>
#include <memory>
#include <vector>

#include <list>

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
    std::vector<std::shared_ptr<Particle> > vectorOfParticles;
   vectorOfParticles.reserve(15);

    for(int i =0;i<10;i++)
    {
        std::shared_ptr<Particle> p (new Particle(i));
        vectorOfParticles.push_back(std::move(p));
    }

    //it will hold pointers to a few elements of vectorOfParticles vector
     std::vector<std::shared_ptr<Particle>> neighboursPointers;

     //iterator over vectorPArticles
     for (std::vector<std::shared_ptr<Particle>>::iterator it=vectorOfParticles.begin();it!=vectorOfParticles.end();it++)
     {
         //save elements' addresses
         neighboursPointers.push_back(/*std::move*/(*it));
     }


     neighboursPointers.push_back(vectorOfParticles[0]);
     neighboursPointers.push_back(vectorOfParticles[1]);
     neighboursPointers.push_back(vectorOfParticles[2]);
     neighboursPointers.push_back(vectorOfParticles[3]);


     //iterator over vectorPArticles
//     std::vector<std::shared_ptr<Particle>>::iterator itVectorOfParticles=vectorOfParticles.begin();
//     for (std::vector<std::shared_ptr<Particle>>::iterator it=neighboursPointers.begin();it!=neighboursPointers.end();it++)
//     {
//         int id = (*it)->id;
//         itVectorOfParticles = find (vectorOfParticles.begin(),vectorOfParticles.end(),
//                                     [id](Particle const& n){
//                                         return n.id == id;
//                                     }

//                                    );

//         if(itVectorOfParticles!= vectorOfParticles.end())//neighboursPointer *it still there in vectorOfParticles
//         {

//         }
//         else
//         {
//             //neighboursPointer *it removed from vectorOfParticles , so we need to delete it from neighboursPointer too

//         }
//     }






     //now delete element vectorOfParticles[1]..->
     vectorOfParticles.erase(vectorOfParticles.begin()+1);
     //now delete element neighboursPointers[1]..->
     neighboursPointers.erase(neighboursPointers.begin()+2);

//     vector<int> v;
//     v.push_back(906);
//     vector<int> * p = &v;
//     cout << (*p)[0] << endl;







     std::vector<std::shared_ptr<Particle>> monitorPool;
     monitorPool.reserve(5);//save invalidation of referencesToPool because of reallocation on monitorPool vecotr

     // pointer to particle pointer..or the address of a particle pointer in the container
     //
     std::vector<std::shared_ptr<Particle>> referencesToPool;
     referencesToPool.resize(5);


     for (int i=0; i<5; ++i)
     {
       std::unique_ptr<Particle> a(new Particle(i));
       monitorPool.push_back(std::move(a));

       referencesToPool[i]=monitorPool[i];

     }


     //save a list with removed indices to use and remove elements in referencesToPool
     std::vector<int>indexToRemovedFromreferenesToPoolVector;

     //Calculate which element to delete
     int saveRemoveIndex=2;

     //DELETE THE 3rd ELEMENT FROM ORIGINAL VECTOR
     std::vector<std::shared_ptr<Particle>>::iterator it; it=monitorPool.begin();
     monitorPool.erase(it+saveRemoveIndex);
     indexToRemovedFromreferenesToPoolVector.push_back(saveRemoveIndex);


     //UPDATE VECTOR "reference to original" vector based on saved "indices to be removed"

     std::vector<std::shared_ptr<Particle>>::iterator it2; it2=referencesToPool.begin();
     for(const auto &el:indexToRemovedFromreferenesToPoolVector)
     {
        referencesToPool.erase(it2+el);
     }



    return 0;
}

