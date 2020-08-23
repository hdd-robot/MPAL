/*
 * Observable.h
 *
 *  Created on: 18 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_
#include <list>
#include <algorithm>
#include <iterator>
#include "Observer.h"

namespace mpal {

template<typename Object>
class Observable {
private:
	std::list<Observer<Object>*> lstObserver;

public:
	Observable() {
	}
	;

	void addObserver(Observer<Object> *obs) {
		if (obs == nullptr) {
			return;
		}
		lstObserver.push_back(obs);
	}

	void removeObserver(Observer<Object> *obs) {
		typename std::list<Observer<Object>*>::iterator it;
		it = std::find(lstObserver.begin(), lstObserver.end(), obs);
		if (it != lstObserver.end()) {
			lstObserver.erase(it);
		}
	}

protected:
	virtual Event<Object>* getEvent()=0;

	void notify() {
		typename std::list<Observer<Object>*>::iterator it;
		for (it = lstObserver.begin(); it != lstObserver.end(); it++) {
			(*it)->refresh(getEvent());
		}
	}

};

} /* namespace mpal */

#endif /* OBSERVABLE_H_ */
