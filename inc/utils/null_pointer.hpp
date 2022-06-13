//
// Created by Anton on 12/06/2022.
//

#ifndef CONTAINERS_NULL_POINTER_HPP
#define CONTAINERS_NULL_POINTER_HPP

//src: https://stackoverflow.com/questions/44517556/how-to-define-our-own-nullptr-in-c98

const                         /* this is a const object...     */
class null_pointer {
public:
	template<class T>          /* convertible to any type       */
	operator T*() const        /* of null non-member            */
	{ return 0; }           /* pointer...                    */

	template<class C, class T> /* or any type of null           */
	operator T C::*() const /* member pointer...             */
	{ return 0; }

private:
	void operator&() const;    /* Can't take address of nullptr */

} null_pointer = {};               /* and whose name is nullptr     */

#endif //CONTAINERS_NULL_POINTER_HPP
