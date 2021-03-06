// projekt.cpp : Defines the entry point for the console application.
//

#include "Interpreter.h"
#include "Procesy.h"
#include "MemoryManager.h"
#include "FileManager.h"
#include "Planista.h"
#include "pipe.h"


int main()
{
	Planista p;
	MemoryManager memoryManager;

	proc_tree tree(&memoryManager, &p);
	FileManager fileManager(&p, &tree);

	Pipeline pipeline(&tree);

	memoryManager.memoryInit();
	Interpreter interpreter(&fileManager, &memoryManager, &tree, &pipeline);
	

	bool loop = true;
	while (true) {
		bool wrong = false;
		std::cout << "\n\n\n-1 zakonczenie petli.\n";
		std::cout << "Podaj numer programu do wczytania: ";
		std::string temp;
		std::cin >> temp;

		int numer = std::stoi(temp);

		switch (numer) {
		case -1: loop = false;  break;

		case 1: temp = "kek1";  tree.fork(new PCB("kek1", 1),  "program1.txt", 69); break;
		case 2: temp = "kek2";  tree.fork(new PCB("kek2", 1), "program2.txt", 96); break;
		case 3: temp = "kek3";  tree.fork(new PCB("kek3", 1),  "program3.txt", 135); break;

		default: std::cout << "Zly numer! Podaj jeszcze raz.\n"; wrong = true; break;
		}
		if (!loop) { break; }
		if (wrong) { continue; }
		interpreter.execute_program(temp);
		tree.exit(tree.find_proc(temp)->PID);
	}

	return 0;
}