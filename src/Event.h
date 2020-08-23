/*
 * Event.h
 *
 *  Created on: 18 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef EVENT_H_
#define EVENT_H_

namespace mpal {

template<typename Object>
class Event {
private:
	Object *object;
public:
	Event(Object *obj) {
		object = obj;
	}
	virtual ~Event() {
		delete object;
	}

	Object* getInfo() {
		return object;
	}

};

} /* namespace mpal */

#endif /* EVENT_H_ */
