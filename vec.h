//
//  vec.h
// BSD 3-Clause License

//~ Copyright (c) 2020, Mashpoe
//~ All rights reserved.

//~ Redistribution and use in source and binary forms, with or without
//~ modification, are permitted provided that the following conditions are met:

//~ 1. Redistributions of source code must retain the above copyright notice, this
   //~ list of conditions and the following disclaimer.

//~ 2. Redistributions in binary form must reproduce the above copyright notice,
   //~ this list of conditions and the following disclaimer in the documentation
   //~ and/or other materials provided with the distribution.

//~ 3. Neither the name of the copyright holder nor the names of its
   //~ contributors may be used to endorse or promote products derived from
   //~ this software without specific prior written permission.

//~ THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//~ AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//~ IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//~ DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//~ FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//~ DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//~ SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//~ CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//~ OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//~ OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//  Created by Mashpoe on 2/26/19.
//

#ifndef vec_h
#define vec_h

#include <stdlib.h>
#include <stdbool.h>

typedef void* vector; // you can't use this to store vectors, it's just used internally as a generic type
typedef size_t vec_size_t; // stores the number of elements
typedef unsigned char vec_type_t; // stores the number of bytes for a type

typedef int*	vec_int;
typedef char*	vec_char;

#ifndef _MSC_VER

// shortcut defines

// vec_addr is a vector* (aka type**)
#define vector_add_asg(vec_addr)			((typeof(*vec_addr))(_vector_add((vector*)vec_addr, sizeof(typeof(**vec_addr)))))
#define vector_insert_asg(vec_addr, pos)	((typeof(*vec_addr))(_vector_insert((vector*)vec_addr, sizeof(typeof(**vec_addr)), pos)))

#define vector_add(vec_addr, value)			(*vector_add_asg(vec_addr) = value)
#define vector_insert(vec_addr, pos, value)	(*vector_insert_asg(vec_addr, pos) = value)

// vec is a vector (aka type*)
#define vector_erase(vec, pos, len)			(_vector_erase((vector*)vec, sizeof(typeof(*vec)), pos, len))
#define vector_remove(vec, pos)				(_vector_remove((vector*)vec, sizeof(typeof(*vec)), pos))

#else

// shortcut defines

// vec is a vector* (aka type**)
#define vector_add_asg(vec_addr, type)				((type*)_vector_add((vector*)vec_addr, sizeof(type)))
#define vector_insert_asg(vec_addr, type, pos)		((type*)_vector_insert((vector*)vec_addr, sizeof(type), pos))

#define vector_add(vec_addr, type, value)			(*vector_add_asg(vec_addr, type) = value)
#define vector_insert(vec_addr, type, pos, value)	(*vector_insert_asg(vec_addr, type, pos) = value)

// vec is a vector (aka type*)
#define vector_erase(vec, type, pos, len)			(_vector_erase((vector*)vec, sizeof(type), pos, len))
#define vector_remove(vec, type, pos)				(_vector_remove((vector*)vec, sizeof(type), pos))

#endif

vector vector_create(void);

void vector_free(vector vec);

void* _vector_add(vector* vec_addr, vec_type_t type_size);

void* _vector_insert(vector* vec_addr, vec_type_t type_size, vec_size_t pos);

void _vector_erase(vector* vec_addr, vec_type_t type_size, vec_size_t pos, vec_size_t len);

void _vector_remove(vector* vec_addr, vec_type_t type_size, vec_size_t pos);

vec_size_t vector_size(vector vec);

vec_size_t vector_get_alloc(vector vec);

#endif /* vec_h */





