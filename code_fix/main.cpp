#include <iostream>
#include <exception>
#include <memory>

/**
 * Need to rename Array to Array2D
 * Need to rename nn and nm to n_row and n_col
*/
class Array {
  public:
    Array(int nn_in, int nm_in)
    : nn(nn_in)
    , nm(nm_in)
    , total_size(nn*nm)
    , data(nullptr)
    {
      data = new int[total_size];
    }

    ~Array() {
      // Make sure to clean up memory!
      // https://stackoverflow.com/questions/10377992/declaring-pointer-to-an-integer-array-c
      // NEED TO deallocate the whole memory data array
      delete[] data;
    }

    void initialise() {
      // Initialise data to 0
      for(int i=0; i<total_size; ++i) {
        // data[i] = 0.0; // should be change to int
        data[i] = 0;
      }
    }

    int& get(int i, int j) {
      // Get value at i,j
      // int idx = i + nn*j;
      int idx = j + nn*i; // IF THE PRINT i -> j
      return data[idx];
    }

    void increment() {
      // Increment all elements
      for (int i=0; i<=nn; ++i) {
        for (int j=0; j<=nm; ++j) {
          get(i, j)+=1;
        }
      }
    }

    bool find(int val) {
      // Search for val in array
      for (int i=0; i<nn; ++i) {
        for (int j=0; j<nm; ++j) {
          if(get(i,j)==val) {
            return true;
          }
        }
      }
      return false;
    }

    void print() {
      // Print to stdout
      for (int i=0; i<nn; ++i) {
        for (int j=0; j<nm; ++j) {
          // std::cout << get(j,i);
          std::cout << get(i,j);
        }
        std::cout << std::endl;
      }
    }

    bool is_square() {
      // Check if array is square
      return nm == nn; 
    }

    void change_size(int nn_in, int nm_in) {
      // Change size of array
      int total_size_new = nn_in*nm_in;
      // Create new data
      auto data_new = new int[total_size_new];
      // Copy old data
      // for(int i=0; i<total_size; ++i) {
      int min_size = std::min(total_size, total_size_new);
      for(int i=0; i<min_size; ++i) { // ISSUE IS HERE, because it copy the size of old data, where it should be new data
        data_new[i] = data[i];
      }
      // Assign new data pointer to old
      delete[] data; // DELETE the old data POINTER before re-assigning
      data = data_new;
      total_size = total_size_new;
      nn = nn_in;
      nm = nm_in;

      // we don't need to delete[] data_new because it will out-of-scope and deleted automatically
      // meanwhile, data new is a member_variable that is carried out through the lifetime of the class
    }


  private:
    int* data;
    
    int nn;
    int nm;
    int total_size;
};

Array* makeSquareArray(int nn, int nm) {
  // https://stackoverflow.com/questions/1371608/c-pointer-to-class
  auto arr_p = new Array(nn, nm);
  // Array* arr_p(new Array(nn, nm));
  // Array arr =  Array(nn, nm);
  // Array* arr_p = &arr;

  // Array* arr_p = new Array(nn, nm);
  if(arr_p->is_square()) {
    std::cout << "Phew, matrix is square" << std::endl;
  } else {
    throw std::invalid_argument("Array isn't square!");
  }
  return arr_p; 
}

void test(bool test_value, const std::string msg = "") {
  std::cout << msg << ": " << (test_value ? ":)" : ":(") << std::endl;
}

int main() {
  Array arr(10, 5);

  std::cout << "Testing increment" << std::endl;
  test(arr.get(1, 2) == 0);
  arr.increment();
  test(arr.get(1, 2) == 1);

  std::cout << "Testing printing" << std::endl;
  arr.print();
  std::cout << "--------------------------------------" << std::endl;
  std::cout << "Testing changing size" << std::endl;
  arr.change_size(5, 5);
  test(arr.get(1, 2) == 1);
  std::cout << "--------------------------------------" << std::endl;
  std::cout << "Testing finding value" << std::endl;
  test(arr.find(4) == false);
  arr.get(4, 3) = 4;
  test(arr.get(4, 3) == 4);
  test(arr.find(4) == true);

  std::cout << "Testing square array throws correct exception" << std::endl;
  try {
    // auto squareArray = makeSquareArray(5, 6);
    Array* squareArray = makeSquareArray(5, 6);
    // DEBUG ISSUE caught here because of memory allocation error in changeSize function above
    // old size = 5 x 10 and resize to 5 x 5
    // L78 // for(int i=0; i<total_size; ++i) {
    // copying the length 10 with only 5 new data, and from data 6 -> 10 memory corrupted (UNDEFINED BEHAVIOUR), but it still passes through
    // that's why the error caught later in this step !!
    squareArray->print();
  } catch (std::invalid_argument &e) {
    // We caught the right exception!
    test(true);
  }

  return 0;
}