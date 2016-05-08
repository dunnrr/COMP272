// commenting from page 154


#ifndef _CIRCLELIST_H_
#define _CIRCLELIST_H_

template <typename E>
class CNode
{
private:
	E elem;
	CNode* next;
	template <typename E>
	friend class CircleList;
};

template <typename E>
class CircleList
{
public:
	CircleList();
	~CircleList();
	bool empty() const;
	const E& front() const;
	const E& back() const;
	void advance();
	void add(const E& e);
	void remove();
private:
	CNode<E>* cursor;
};

/*template <typename E>
CircleList<E>::CircleList();

template <typename E>
CircleList<E>::~CircleList();

template <typename E>
bool CircleList<E>::empty() const;

template <typename E>
const E& CircleList<E>::front() const;

template <typename E>
const E& CircleList<E>::back() const;

template <typename E>
void CircleList<E>::advance();

template <typename E>
void CircleList<E>::add(const E& e);

template <typename E>
void CircleList<E>::remove();
*/
#endif