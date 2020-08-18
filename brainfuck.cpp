#include <iostream>
#include <fstream>
#include <cstring>

#define MEMORY_SIZE 512

using namespace std;

void jump(char *& code_ptr, unsigned char *& mem_ptr) {
  int dir = *code_ptr == '[' ? 1 : -1;
  int depth = 1;

  while (depth) {
    code_ptr += dir;
    if (*code_ptr == '[') {
      depth += dir;
    } else if (*code_ptr == ']') {
      depth -= dir;
    }
  }
}

int main(int argc, char ** argv) {
  char * filename = argv[1];

  unsigned char mem[MEMORY_SIZE];
  char code[MEMORY_SIZE];

  unsigned char * mem_ptr = mem;
  char * code_ptr = code;

  int depth = 0;

  ifstream codefile(filename);

  if (codefile.is_open()) {
    codefile.read(code, MEMORY_SIZE);
    while (*code_ptr != 0) {
      switch (*code_ptr) {
        case '>':
          mem_ptr++;
          break;
        
        case '<':
          mem_ptr--;
          break;

        case '+':
          (*mem_ptr)++;
          break;

        case '-':
          (*mem_ptr)--;
          break;

        case '.':
          cout << (*mem_ptr);
          break;

        case ',':
          (*mem_ptr) = cin.get();
          break;

        case '[':
          if (!(*mem_ptr)) {
            jump(code_ptr, mem_ptr);
          }
          break;
        case ']':
          if (*mem_ptr) {
            jump(code_ptr, mem_ptr);
          }
          break;
        default:
          cerr << "Unknown op code" << endl;
      }
      code_ptr++;
    }

    cout << endl << "Program ended successfully" << endl << mem << endl;
    return 0;
  }
  else {
    cerr << "Unable to open file";
    return 1;
  }
}