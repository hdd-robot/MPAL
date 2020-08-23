/*
 * Observer.h
 *
 *  Created on: 18 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "Event.h"

namespace mpal {

template<typename Object>
class Observer {
public:
	Observer() {
	}
	;

	virtual void refresh(Event<Object> *e)=0;
};

} /* namespace mpal */

#endif /* OBSERVER_H_ */
