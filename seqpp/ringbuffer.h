#ifndef RINGBUFFER_HH
#define RINGBUFFER_HH

#include <jack/ringbuffer.h>
#include <memory>
#include <iostream>

/**
	T needs to be a default constructable type.. And it has to have valid
	copy constructor/assignment operator

	Note that this class needs to construct n objects of type T (with n == size)  so 
	that the places in the ringbuffer become assignable

	Note that the objects remain in the ringbuffer until they are overwritten again
	when the ringbuffer returns to the current position the next time around. I.e. a
	read() does not assign a T() to the read object as that could cause destructors
	to be called, etc..

	Note that read() creates a copy of the T, so the T(const T&) should be non blocking
*/
template <class T> 
struct ringbuffer {
	unsigned int size;

	jack_ringbuffer_t *jack_ringbuffer;

	ringbuffer(unsigned int size = 1024) : size(size) {
		jack_ringbuffer = jack_ringbuffer_create(sizeof(T) * size);
		std::cout << "write space: " << jack_ringbuffer_write_space(jack_ringbuffer) << std::endl;

		for (unsigned int i = 0; i < size; ++i) {
			T *t = new (jack_ringbuffer->buf + sizeof(T) * i) T();
		}
	}

	~ringbuffer() {
		for (unsigned int i = 0; i < size; ++i) {
			((T*)(jack_ringbuffer->buf + sizeof(T) * i))->~T();
		}

		jack_ringbuffer_free(jack_ringbuffer);
	}

	bool empty() {
		// std::cout << "space: " << jack_ringbuffer_write_space(jack_ringbuffer) <<  " sizeof(T): " << sizeof(T) << " size: " << size << std::endl;
		return jack_ringbuffer_write_space(jack_ringbuffer) >= sizeof(T) * (size - 1);
	}

	bool can_write() {
		if (jack_ringbuffer_write_space(jack_ringbuffer) >= sizeof(T)) {
			return true;
		}

		return false;
	}

	void write(const T &t) {
		jack_ringbuffer_data_t rb_data[2];
		jack_ringbuffer_get_write_vector(jack_ringbuffer, rb_data);
		*((T*)rb_data->buf) = t;
		jack_ringbuffer_write_advance(jack_ringbuffer, sizeof(T));
	}

	bool can_read() {
		if (jack_ringbuffer_read_space(jack_ringbuffer) >= sizeof(T)) {
			return true;
		}

		return false;
	}

	T* peek() {
		if (false == can_read()) return 0;

                jack_ringbuffer_data_t rb_data[2];
                jack_ringbuffer_get_read_vector(jack_ringbuffer, rb_data);
                return ((T*)rb_data->buf);
	}

	/*
		read a T from the ringbuffer and replace it with a default constructed one.
		NOTE: this is only suitable for shared_ptr or similar
	*/
	T read() {
		T *tp = peek();

		T t = *tp;

		*tp = T();
		
		jack_ringbuffer_read_advance(jack_ringbuffer, sizeof(T));
		return t;
	}
};

#endif
