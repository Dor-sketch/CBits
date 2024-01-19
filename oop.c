#include "oop.h"
#include <stdio.h>
#include <stdlib.h>

/* warpper function to enable unified interface polymorphsim */
void animal_speak(struct Animal *animal) {
	animal->vptr->functions[ANIMAL_SPEAK](animal);
}

/* default implementation for animal */
void default_speak(struct Animal *animal) {
	printf("Hello! I'm %s!\n", animal->name);
}

/* override for dog */
void dog_speak(struct Animal *animal) {
	printf("Woof! I'm %s!\n", animal->name);
}

/* override for cat */
void cat_speak(struct Animal *animal) {
	printf("Meow! I'm %s!\n", animal->name);
}

/* override for labrador */
void labrador_speak(struct Animal *animal) {
	printf("Woof! I'm a Labrador named %s!\n", animal->name);
}

/* New function for labrador */
void labrador_play_fetch(struct Dog *dog) {
	printf("I'm a Labrador named %s and I'm playing fetch!\n",
		   dog->animal.name);
}

/* VTables */
static struct VTable default_vtable = {&default_speak}; /* init with default */
static struct VTable dog_vtable = {&dog_speak};
static struct VTable cat_vtable = {&cat_speak};
// labrador_vtable inherits from dog_vtable and overrides speak + adds
// play_fetch
static struct VTable labrador_vtable = {
	.functions =
		{
			&dog_speak,
			&labrador_play_fetch,
		},
};

/* Constructors */
struct Animal *animal_new(char *name) {
	struct Animal *animal = malloc(sizeof(struct Animal));
	animal->name = name;
	animal->vptr = &default_vtable; // Set the default vtable
	return animal;
}

struct Dog *dog_new(char *name) {
	struct Dog *dog = malloc(sizeof(struct Dog));
	dog->animal.name = name;
	dog->animal.vptr = &dog_vtable;
	return dog;
}

struct Labrador *labrador_new(char *name) {
	struct Labrador *labrador = malloc(sizeof(struct Labrador));
	labrador->dog.animal.name = name;
	labrador->dog.animal.vptr = &labrador_vtable;
	labrador->dog.breed = "Labrador";
	return labrador;
}

struct Cat *cat_new(char *name) {
	struct Cat *cat = malloc(sizeof(struct Cat));
	cat->animal.name = name;
	cat->animal.vptr = &cat_vtable;
	return cat;
}

/* Destructor */
void animal_free(struct Animal *animal) { free(animal); }

int main() {
	printf("OOP in C\n");
	printf("Size of Animal: %lu\n", sizeof(struct Animal));
	printf("Size of Cat: %lu\n", sizeof(struct Cat));
	printf("Size of Dog: %lu\n", sizeof(struct Dog));
	printf("Size of Labrador: %lu\n", sizeof(struct Labrador));

	struct Animal *example[4];

	// Create some animals
	example[0] = animal_new("Animal");
	example[2] = (struct Animal *)cat_new("Cat");
	example[1] = (struct Animal *)dog_new("Dog");
	example[3] = (struct Animal *)labrador_new("Blacky");

	// Call the speak function via the wrapper
	for (int i = 0; i < 4; i++) {
		animal_speak(example[i]);
	}

	// or via the animal pointer
	// animal->vptr->functions[ANIMAL_SPEAK](animal);

	// for example, labrador has an extra function that dog doesn't have
	((struct Labrador *)example[3])
		->dog.animal.vptr->functions[ANIMAL_PLAY_FETCH](
			(struct Animal *)example[3]);

	// Free the memory
	for (int i = 0; i < 4; i++) {
		animal_free(example[i]);
	}

	return 0;
}