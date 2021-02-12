/** \file TVector.c
 *  \brief Implementace Basic Vector API
 *  \author Petyovský
 *  \version 2021
 *  $Id: TVector.c 1023 2021-02-08 09:42:15Z petyovsky $
 */

#include <stdlib.h>
#include <assert.h>
#include "TVector.h"
#include "check.h"


bool vector_init(struct TVector *aVector, size_t aSize)
	{
		if (!aVector)
			return false;
		aVector->iValues = (TVectorElement*)calloc(aSize, sizeof(TVectorElement));
		aVector->iSize = aSize;
		return true;
	}

bool vector_init_random(struct TVector *aVector, size_t aSize)
	{
		if (!aVector)
			return false;
	    aVector->iValues= (TVectorElement*)calloc(aSize, sizeof(TVectorElement));
		aVector->iSize = aSize;
	
		for (int i=0;i<aSize;i++)
		{
			aVector->iValues[i] = rand();
		}

		return true;
	
	
	}

bool vector_init_file(struct TVector *aVector, FILE *aInputFile)
	{
		return false;
	}

bool vector_clone(const struct TVector *aVector, struct TVector *aVectorClone)
	{
		if (!aVector)
			return false;
		//aVectorClone = aVector; <- warning pri kompilacii lebo const struct vs struct
		aVectorClone->iSize = aVector->iSize;
		aVectorClone->iValues = aVector->iValues;

		//free(aVector->iValues);
		return true;
	}

bool vector_store_file(const struct TVector *aVector, FILE *aOutputFile)
	{
	return false;
	}

TVectorElement vector_value(const struct TVector *aVector, size_t aPos)
	{
	return (TVectorElement) { 0 };
	}

void vector_set_value(struct TVector *aVector, size_t aPos, TVectorElement aValue)
	{
	}

size_t vector_size(const struct TVector *aVector)
	{
	return 0;
	}

bool vector_resize(struct TVector *aVector, size_t aNewSize)
	{
		if (!aVector)
			return false;
		TVectorElement* newValues = (TVectorElement*)calloc(aNewSize,sizeof(TVectorElement));
		size_t upper_border = (aVector->iSize > aNewSize) ? aNewSize : aVector->iSize;
		for(size_t i=0;i< upper_border;i++)
		{ 
			newValues[i] = aVector->iValues[i];
		}
		
		aVector->iValues = newValues;
		aVector->iSize = aNewSize;
		free(newValues);
		return true;
	}

void vector_destroy(struct TVector *aVector)
	{
		if (!aVector)
			return;
		//free(aVector->iValues); // <- vraj chybne
	
	}

struct TVectorIterator vector_iterator_begin(const struct TVector *aVector)
	{
	return (struct TVectorIterator) { .iVector = NULL, .iPos = 0 };
	}

struct TVectorIterator vector_iterator_pos(const struct TVector *aVector, size_t aPos)
	{
	return (struct TVectorIterator) { .iVector = NULL, .iPos = 0 };
	}

bool vector_iterator_is_valid(const struct TVectorIterator *aIter)
	{
	return false;
	}

bool vector_iterator_to_next(struct TVectorIterator *aIter)
	{
	return false;
	}

bool vector_iterator_to_prev(struct TVectorIterator *aIter)
	{
	return false;
	}

TVectorElement vector_iterator_value(const struct TVectorIterator *aIter)
	{
	return (TVectorElement) { 0 };
	}

bool vector_iterator_set_value(const struct TVectorIterator *aIter, TVectorElement aValue)
	{
	return false;
	}
