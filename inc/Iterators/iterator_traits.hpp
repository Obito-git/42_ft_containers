//
// Created by Anton on 10/06/2022.
//

#ifndef CONTAINERS_ITERATOR_TRAITS_HPP
#define CONTAINERS_ITERATOR_TRAITS_HPP

namespace ft {
	template<class C, class T, class Dist = ptrdiff_t,
			class Pt = T *, class Rt = T &>
	struct iterator_traits {
		typedef C iterator_category;
		typedef T value_type;
		typedef Dist difference_type;
		typedef Pt pointer;
		typedef Rt reference;
	};

	struct input_iterator_tag {
	};
	struct forward_iterator_tag
			: public input_iterator_tag {
	};
	struct bidirectional_iterator_tag
			: public forward_iterator_tag {
	};
	struct random_access_iterator_tag
			: public bidirectional_iterator_tag {
	};
}
#endif //CONTAINERS_ITERATOR_TRAITS_HPP
