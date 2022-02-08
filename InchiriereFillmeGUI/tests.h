#pragma once
#include "controller.h"
#include <assert.h>

/*
	Tests for the entities in the domain
*/
void testDomain();

/*
	Tests for RepoInMemory
*/
void testRepoInMemory();

/*
	Tests for the RepoFile
*/
void testRepoFile();

/*
	Tests for the controller
*/
void testController();

/*
	Tests for the validator
*/
void testValidator();

/*
	Tests for searching, sorting and filtering
*/
void testSearchSortFilter();

/*
	Tests for the renting cart
*/
void testCart();

/*
	Tests for undo
*/
void testUndo();

void testRepoLab();
void testRepoLabWithExceptions();