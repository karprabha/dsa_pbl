#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cstdlib>

namespace nstd{
	template <typename T>
	struct Node{
		T data;
		Node<T>* next;
	};

	template <typename T>
	class LinkedList{
		Node<T>* start;
		Node<T>* end;
		unsigned int linkedlistSize;
		Node<T>* create_newnode();
		Node<T>* get(const unsigned int& index) const;
	public:
		LinkedList();
		void append(const T& data);
		void pop();
		T& at(const unsigned int& index) const;
		void add(const unsigned int& index,const T& data);
		void del(const unsigned int& index);
		void add_beg(const T& data);
		void del_beg();
		void swap(const unsigned int& index1,const unsigned int& index2);
		unsigned int size() const;
		~LinkedList();

	};

	class EmptyListException{

	};

	template <typename T>
	Node<T>* LinkedList<T>::create_newnode(){
		try{
			Node<T>* newnode = new Node<T>();
			return newnode;
		}
		catch(const std::bad_alloc& e){
			std::cout<<"ERROR!! Memory allocation is failed : "<<e.what()<<std::endl;
			abort();
		}
	}

	template <typename T>
	Node<T>* LinkedList<T>::get(const unsigned int& index) const{
		if(index == linkedlistSize -1)
			return end;

		unsigned int count=0;
		Node<T>* temp = start;
		
		while((temp != NULL)&&(count != index)){
			temp = temp->next;
			count++;
		}
		return temp;
	}

	template <typename T>
	LinkedList<T>::LinkedList(){
		start = NULL;
		end = NULL;
		linkedlistSize = 0;
	}

	template <typename T>
	void LinkedList<T>::append(const T& data){
		if(!start){
			Node<T>* newnode = create_newnode();
			start = newnode;
			end = newnode;
			end->next = NULL;
			newnode->data = data;
			linkedlistSize++;
		}
		else{
			Node<T>* newnode = create_newnode();
			end->next = newnode;
			end = newnode;
			end->next = NULL;
			newnode->data = data;
			linkedlistSize++;
		}
	}

	template <typename T>
	void LinkedList<T>::pop(){
		try{
			if(linkedlistSize == 0)
				throw EmptyListException();

			if(linkedlistSize == 1){
				Node<T>* temp = end;
				end = NULL;
				start = NULL;
				delete temp;
				linkedlistSize--;
			}
			else{
				Node<T>* head = get(linkedlistSize-2);
				Node<T>* temp = end;
				end = head;
				end->next = NULL;
				delete temp;
				linkedlistSize--;
			}
		}
		catch(EmptyListException& e){
			std::cout<<"ERROR: Invalid operation on empty list "<<std::endl;
			abort();
		}
	}

	template <typename T>
	T& LinkedList<T>::at(const unsigned int& index) const{
		try{
			if(index > linkedlistSize-1)
				throw std::out_of_range ("abort called after throwing an instance of \'std::out_of_range\'");
			else if(linkedlistSize == 0)
				throw EmptyListException();

			Node<T>* newnode = get(index);
			return newnode->data;
		}
		catch(const std::out_of_range& e){
			std::cout<<"ERROR: "<<e.what()<<std::endl;
			abort();
		}
		catch(EmptyListException& e2){
			std::cout<<"ERROR: Invalid operation on empty list "<<std::endl;
			abort();
		}
	}

	template <typename T>
	void LinkedList<T>::add(const unsigned int& index,const T& data){
		try{
			if(index > linkedlistSize)
				throw std::out_of_range ("abort called after throwing an instance of \'std::out_of_range\'");

			if(index == linkedlistSize)
				append(data);
			else if(index == 0)
				add_beg(data);
			else{
				Node<T>* temp = get(index-1);
				Node<T>* newnode = create_newnode();
				newnode->next = temp->next;
				temp->next = newnode;
				newnode->data = data;
				linkedlistSize++;			
			}
		}
		catch(const std::out_of_range& e){
			std::cout<<"ERROR: "<<e.what()<<std::endl;
			abort();
		}
	
	}

	template <typename T>
	void LinkedList<T>::del(const unsigned int& index){
		try{
			if(index > linkedlistSize-1)
				throw std::out_of_range ("abort called after throwing an instance of \'std::out_of_range\'");
			else if(linkedlistSize == 0)
				throw EmptyListException();

			if(index == linkedlistSize-1)
				pop();			
			else if(index == 0)
				del_beg();
			else{
				Node<T>* head = get(index-1);
				Node<T>* temp = head->next;
				head->next = temp->next;
				delete temp;
				linkedlistSize--;		
			}
		}
		catch(const std::out_of_range& e){
			std::cout<<"ERROR: "<<e.what()<<std::endl;
			abort();
		}
		catch(EmptyListException& e2){
			std::cout<<"ERROR: Invalid operation on empty list "<<std::endl;
			abort();
		}	
	}

	template <typename T>
	void LinkedList<T>::add_beg(const T& data){
		if(linkedlistSize==0)
			append(data);
		else{
			Node<T>* newnode = create_newnode();
			newnode->next = start;
			start = newnode;
			newnode->data = data;
			linkedlistSize++;
		}	
	}

	template <typename T>
	void LinkedList<T>::del_beg(){
		if(linkedlistSize==1)
			pop();
		else{
			Node<T>* temp = start;
			start = temp->next;
			delete temp;
			linkedlistSize--;
		}
	}

	template <typename T>
	void LinkedList<T>::swap(const unsigned int& index1,const unsigned int& index2){
		try{
			if((index1 > linkedlistSize-1)||(index2 > linkedlistSize-1))
				throw std::out_of_range ("abort called after throwing an instance of \'std::out_of_range\'");

			if(index1 == index2){
				//do nothing
			}

			Node<T>* temp = NULL;
			Node<T>* m_index1 = get(index1);
			Node<T>* m_index2 = get(index2);
			Node<T>* m_index1_prev = NULL;
			Node<T>* m_index2_prev = NULL;
			
			if(index1>0)
				m_index1_prev = get(index1-1);
			if(index2>0)
				m_index2_prev = get(index2-1);

			if(m_index1_prev != NULL)
				m_index1_prev->next = m_index2;
			else
				start = m_index2;

			if(m_index2_prev != NULL)
				m_index2_prev->next = m_index1;
			else
				start = m_index1;

			temp = m_index1->next;
			m_index1->next = m_index2->next;
			m_index2->next = temp;

			if(m_index1->next == NULL)
				end = m_index1;
			else if(m_index2->next == NULL)
				end = m_index2;
		}
		catch(const std::out_of_range& e){
			std::cout<<"ERROR: "<<e.what()<<std::endl;
			abort();
		}
	}

	template <typename T>
	unsigned int LinkedList<T>::size() const{
		return linkedlistSize;
	}

	template <typename T>
	LinkedList<T>::~LinkedList(){
		while(linkedlistSize!=0)
			pop();
	}
}


#endif