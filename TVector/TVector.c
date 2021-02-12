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
		if (aSize > 0)
		{
			aVector->iValues = calloc(aSize, sizeof(TVectorElement));
			aVector->iSize = aSize;
			return true;
		}
		return false;
		
	}

bool vector_init_random(struct TVector* aVector, size_t aSize)
	{
		if (!aVector)
			return false;
		if (aSize > 0)
		{

			TVectorElement* newValues = (TVectorElement*)calloc(aSize, sizeof(TVectorElement));
			for (size_t i = 0; i < aSize; i++)
			{
				newValues[i] = vector_element_random_value();

			}
			aVector->iValues = newValues;
			aVector->iSize = aSize;
			free(newValues);
			return true;
		}
		return false;
	}
	
	
	

bool vector_init_file(struct TVector *aVector, FILE *aInputFile)
	{
		return false;
	}

bool vector_clone(const struct TVector *aVector, struct TVector *aVectorClone)
	{
		if (!aVector || !aVectorClone)
			return false;
		//aVectorClone = aVector; <- warning pri kompilacii lebo const struct vs struct
		aVectorClone->iSize = aVector->iSize;
		aVectorClone->iValues = aVector->iValues;
			
		return true;
	}

bool vector_store_file(const struct TVector *aVector, FILE *aOutputFile)
	{
	return false;
	}

TVectorElement vector_value(const struct TVector *aVector, size_t aPos)
	{
	return (TVectorElement) { (aPos>=0)?aVector->iValues[aPos]:0 };
	}

void vector_set_value(struct TVector *aVector, size_t aPos, TVectorElement aValue)
	{
		if (!aVector)
			return 0;
		if ((aPos >= 0) && (aValue))
		{
			aVector->iValues[aPos] = aValue;
		}
		return;
	}

size_t vector_size(const struct TVector *aVector)
	{
		if (!aVector)
			return 0;
		return(aVector->iSize);
	}

bool vector_resize(struct TVector *aVector, size_t aNewSize)
	{
		if (!aVector)
			return false;
		TVectorElement* newValues = (TVectorElement*)calloc(aNewSize,sizeof(TVectorElement));
		//potrebujem obmedzit hornu hranicu pre kopirovanie
		//beriem mensie z aVector->iSize a aNewSize
		size_t upper_border = (aVector->iSize > aNewSize) ? aNewSize : aVector->iSize;
		for(size_t i=0;i< upper_border;i++)
		{ 
			newValues[i] = aVector->iValues[i]; //bez obmedzenie by to kopirovalo cudzie data
		}
		
		aVector->iValues = newValues;
		aVector->iSize = aNewSize;
		free(newValues);
		return true;
	}

void vector_destroy(struct TVector* aVector)
{
	if (!aVector)
		return;
	free(aVector->iValues);
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
