#ifndef SEQPP_GC_HH
#define SEQPP_GC_HH

#include <list>
#include <boost/thread.hpp>


using std::list;
using boost::thread;
using boost::bind;

namespace seqpp {

/*
	T needs to have a unique() method to determine 
	whether it's the last reference to an object
*/
template<class T>
struct gc {
	list<T> heap;

	typedef list<T> list_type;

	bool quit;

	gc() : 
		quit(false),
		gc_thread(bind(&gc::gc_worker, this)) 
	{ }

	~gc() {
		quit = true;
		gc_thread.join();
	}

	void gc_worker() {
		std::cout << "gc starting up" << std::endl;
		while(false == quit) {
			for (typename list_type::iterator it = heap.begin(); it != heap.end();) {
				if (it->unique()) {
					std::cout << "something's gotta give" << std::endl;
					it = heap.erase(it);
				} else {
					++it;
				}
			}
			usleep(10000);
		}
		std::cout << "gc going away" << std::endl;
	}

	protected:
	thread gc_thread;
};

} // namespace

#endif

