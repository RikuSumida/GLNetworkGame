#pragma once
//------------------------------------------------------------------------------
// Title:			List
// File Name:		list.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/05/16
// Updated:			2016/09/17
//------------------------------------------------------------------------------
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

//------------------------------------------------------------------------------
// CLASS
//------------------------------------------------------------------------------
template < class T >
class List
{
private:
	//--------------------------------------
	// STRUCTURES
	//--------------------------------------
	struct Node
	{
		T data;
		Node* next;
		Node* prev;
	};

public:
	//--------------------------------------
	// CLASSES
	//--------------------------------------
	class Iterator
	{
	friend class List;
	public:
		Iterator( Node* n = nullptr ) :
			node( n )
		{}

		bool AtEnd( void )
		{
			return node ? false : true;
		}

		Iterator& operator++()
		{
			if( !node )
			{
				node = nullptr;
			}

			else
			{
				node = node->next;
			}

			return *this;
		}

		Iterator operator++( int )
		{
			Node* current = node;

			if( !node )
			{
				node = nullptr;
			}

			else
			{
				node = node->next;
			}

			return Iterator( current );
		}

		Iterator& operator--()
		{
			if( !node )
			{
				node = nullptr;
			}

			else
			{
				node = node->prev;
			}

			return *this;
		}

		T& operator *()
		{
			return node->data;
		}

	private:
		Node* GetNode( void )
		{
			return node;
		}

		Node* node;
	};

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Constructor / Destructor
	List() :
		top( nullptr ),
		bot( nullptr ),
		it( nullptr ),
		size( 0 )
	{}

	~List(){}

	// List Functions
	// リストの関数
	// Push Item to Front of List
	void PushFront( T item )
	{
		size++;

		// If List is Empty
		// リストは空っぽ
		if( !top )
		{
			top = new Node;
			bot = top;
			top->data = item;
			top->prev = nullptr;
			top->next = nullptr;
		}

		// Else, Create New Top of List
		// リストの新しいトップを作る
		else
		{
			Node* newTop = new Node;
			newTop->next = top;
			top->prev = newTop;
			top = newTop;
			top->data = item;
			top->prev = nullptr;
		}
	}

	// Push back Item to End of List
	void PushBack( T item )
	{
		size++;

		// If List is Empty
		// リストは空っぽ
		if( !bot )
		{
			top = new Node;
			bot = top;
			top->data = item;
			top->prev = nullptr;
			top->next = nullptr;
		}

		// Else, Push to Back of List
		// リストに最後にプッシュ
		else
		{
			bot->next = new Node;
			bot->next->prev = bot;
			bot = bot->next;
			bot->data = item;
			bot->next = nullptr;
		}
	}

	// Insert Item at Iterator Point
	void Insert( T item, Iterator iter )
	{
		it = iter.GetNode();
		
		// If Iterator Set
		// IteratorがNullじゃない
		if( it )
		{
			// If Iterator not at Top of List
			// リストのトップじゃない場合
			if( it != top )
			{
				size++;

				Node* newItem = new Node;
				it->prev->next = newItem;
				newItem->prev = it->prev;
				newItem->next = it;
				it->prev = newItem;
				newItem->data = item;
				return;
			}

			else
			{
				PushFront( item );
				return;
			}
		}

		else
		{
			PushFront( item );
			return;
		}
	}
	
	// Remove All Matching Items
	void Remove( T item )
	{
		if( top )
		{
			Node* curr = top;

			// While Current Node Exists
			while( curr )
			{
				// If Item to Remove Matches
				if( curr->data == item )
				{
					// If Front of List
					if( curr == top )
					{
						size--;

						top = top->next;

						// If Iterator is at Current
						if( it == curr )
						{
							it = top;
						}

						delete curr;
						curr = top;

						// If Top Remains
						if( top )
						{
							top->prev = nullptr;
						}

						// No More Items on List
						else
						{
							bot = nullptr;
							return;
						}
					}

					// If End of List
					else if( curr == bot )
					{
						size--;

						curr->prev->next = nullptr;
						bot = curr->prev;

						// If Iterator is at Current
						if( it == curr )
						{
							it = bot;
						}

						delete curr;
						curr = bot;
						return;
					}

					// Middle of List
					else
					{
						size--;

						curr->prev->next = curr->next;
						curr->next->prev = curr->prev;
						Node* hold = curr->prev;

						// If Iterator is at Current
						if( it == curr )
						{
							it = curr->prev;
						}

						delete curr;
						curr = hold;
					}
				}

				else
				{
					curr = curr->next;
				}
			}
		}
	}

	// Get Top of List and Set Iterator
	Iterator Begin( void )
	{
		Iterator it( top );
		return it;
	}

	// Get End of List and Set Iterator
	Iterator End( void )
	{
		Iterator it( bot );
		return it;
	}

	// Get Top of List
	// ( !Check if List is Empty before using! )
	T Front( void )
	{
		return top->data;
	}

	// Get Bottom of List
	// ( !Check if List is Empty before using! )
	T Back( void )
	{
		return bot->data;
	}

	// Get List Size
	int Size( void )
	{
		return size;
	}

	// If List is Empty
	bool Empty( void )
	{
		return !size;
	}

	// Pop Front from List
	void PopFront( void )
	{
		// If List is Empty
		// リストは空っぽ
		if( !top )
		{
			return;
		}

		// Get Old Top Pointer
		Node* topOld = top;

		// If Top Next Exists
		if( top->next )
		{
			top = top->next;
			top->prev = nullptr;
		}

		else
		{
			top = nullptr;
			bot = nullptr;
		}

		// Delete Old Top
		// 古いトップを削除
		delete topOld;

		// Decrease Size
		size--;
	}


private:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	Node* top;		// Top of List
	Node* bot;		// Bottom of List
	Node* it;		// List Iterator
	int size;		// List Size
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif