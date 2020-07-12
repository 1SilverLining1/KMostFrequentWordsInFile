#include<bits/stdc++.h> 
using namespace std ; 

struct TrieNode 
{
	bool IsEnd ;
	int index ;
	TrieNode * children [ 26 ] ; 
	int frequency ; 
	TrieNode ()
	{
	
		IsEnd = false ; 
		index = -1 ; 
		frequency = 0 ;
		for ( int i = 0 ; i < 26 ; i ++ ) 
			children [ i ] = NULL ;  
	}
};

struct HeapNode
{
	string word ; 
	int frequency ; 
	TrieNode * trienode ; 
	
	HeapNode ()
	{
		frequency  = 0 ; 
		trienode = NULL ; 
	}
	
};

class Heap
{
	
	
	int capacity ; 
	int size ; 
	HeapNode * arr  ; 
	
	public : 
	
	Heap( int capacity )
	{
		this -> capacity = capacity ; 
		size = 0 ; 
		arr = new HeapNode [ capacity ] ; 
	}
	void swap ( int idx1 , int idx2 )
	{
			HeapNode temp = arr [ idx1 ] ; 
			arr [ idx1 ] = arr [ idx2 ] ; 
			arr [ idx2 ] = temp ; 
			arr [ idx1 ] .trienode -> index = idx1 ; 
			arr [ idx2 ] .trienode -> index =idx2 ; 
	}
	void heapify( int index )
	{
		int left = 2 * index + 1 ; 
		int right = 2 * index + 2 ; 
		int mini = index ; 
		
		if ( left < size and arr [ left ] .frequency  < arr [ index ] .frequency )
			mini = left ; 
			
		if ( right < size and arr [ right ] .frequency  < arr [ index ] .frequency )
			mini = right ; 
		
		if ( index != mini )
		{
			swap ( index , mini ) ; 
			heapify ( mini ) ; 
		}
		
	}
	
	void buildheap ( int index )
	{
	
		while ( index > 0 and arr [ index ] .frequency < arr [ index/ 2 ] .frequency )
		{
			
			swap ( index , index / 2 ) ;
			
			index = index / 2 ; 
		}	
	}
	void insert ( TrieNode * node  , string word )
	{
		int index = node -> index ;
		int frequency = node -> frequency ;		
		if  (  index != -1 )
		{
			arr [ index ] .frequency = frequency  ; 
			heapify ( 0 ) ;  
		}
		else if ( size < capacity )
		{
			arr [ size ].frequency = frequency ; 
			arr [ size] .word = word ; 
			arr [ size  ] . trienode = node ;
			node -> index = size ; 
			buildheap ( size ) ; 
			size ++ ; 
		}
		else if ( arr [ 0 ].frequency < frequency )
		{
		
			arr [ 0 ] . trienode -> index = -1 ; 
			arr [ 0 ].frequency = frequency ; 
			arr [ 0 ] .word = word ; 
			arr [ 0 ] . trienode = node ; 
			heapify ( 0 ) ;  
		}
	}
	
	void display ()
	{
		for ( int i = 0 ; i < capacity ; i ++ )
		{
				cout << arr [ 0] .word << " " << arr [ 0 ].frequency << endl ; 
				swap ( 0 , size - 1 ) ; 
				size -- ; 
				heapify ( 0 ) ; 
		}
	}
};


class Trie 
{
	TrieNode * root ; 
	
	public :
	
	
	Trie ()
	{
		root = new TrieNode () ; 
	} 	
	
	
	TrieNode * insert ( string word ,  Heap * hp )
	{
		TrieNode * temp = root ; 
		
		int n = word.length() ; 
		for ( int i = 0 ; i < n ; i ++ )
		{
			TrieNode * ptr = temp -> children [ word [ i ] - 'a' ] ;
			if ( ptr ==NULL ) 
				 temp  -> children [ word [ i ] - 'a' ]  = new TrieNode () ; 
			temp = 	 temp  -> children [ word [ i ] - 'a' ]  ; 
			
		}
		
		temp -> IsEnd = 1 ; 
		temp -> frequency ++ ; 
		hp -> insert ( temp , word ) ; 
		
	}
};

void KMostFrequentWordsInFile( string  filename  , int k )
{
	ifstream in ; 
	in.open ( filename.c_str() ) ; 
	string word ;
	Trie * trie = new Trie () ; 
	
	Heap * hp= new Heap ( k )  ; 
	while ( in >> word  )
	{
		trie-> insert ( word , hp ) ;
	}
	
	hp-> display() ; 
	in.close () ; 
}

int main()
{
	int k ; 
	k = 3 ;
	//cin >> k ; 
	string filename = "kmp"; 
	//cin >> filename ; 
	KMostFrequentWordsInFile  ( filename  , k ) ;  
}
