/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Brandon Cao
 * Date        : November 27th, 2019
 * Description : Solves the all pairs shortest paths problem with Floyd’s algorithm. 
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip> 
#include <fstream>
#include <sstream>

using namespace std;

char valid_range_value[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; 
const long INF = 0x1000000000000;
int num_vertices;

unsigned int len(unsigned int num) {
    int count = 0;
    while(num != 0) {
        num = num/10;
        count++;
    }
    return count;
}

int edge_data(string str) {
    string word;
    int count = 0;
    stringstream line(str);
    
    while(line >> word) {
        count++;
    }
    return count;  
}

bool check_components(ifstream &text_file) {
    string str;
    int line_num = 0;

    text_file.clear();
    text_file.seekg(0, ios::beg);
    while(getline(text_file, str)) {
        line_num++;
        if(str.size() > 0) {
            if(line_num == 1) {
                continue;
            }
            int count = edge_data(str);
            if (count != 3) {
                cerr<<"Error: Invalid edge data '" << str << "' on line "<< line_num <<"."<<endl;
                return false;
            }
        } else {
            continue;
        }
    }
    return true;
}

int edge_weight(string str ) {
    string word;
    int count = 0;
    stringstream line(str);
    
    while(line >> word) {
        count++;
        if(count == 1 || count == 2)
            continue; 
        stringstream tmp(word);
        int x = 0;
        tmp >> x;
        return x;
    }
    return -1;  
}

bool check_edge_weight(ifstream &text_file) {
    string str;
    int line_num = 0;

    text_file.clear();
    text_file.seekg(0, ios::beg);
    while (getline(text_file, str)) {
         line_num++;
         if(str.size() > 0) {
            if(line_num == 1) {  
                continue;
            }
            // count components 
            int weight = edge_weight(str);
            if(weight <= 0) {
                cerr << "Error: Invalid edge weight '" << &str[4] << "' on line " << line_num << "." << endl;
                return false;
            } 
         }
         else {
            continue;
         }
    }
    return true;
}

bool check_vertex_range(ifstream &text_file, int num_vertices) {
    int line_num = 0, count = 0, letter = 0;
    string str, word;
    bool b_inrange = true;

    text_file.clear();
    text_file.seekg(0, ios::beg);
    while (getline(text_file, str)) {
        line_num++;
        if(str.size() > 0) {
            if(line_num == 1) {  
                continue;
            }
            count = 0;
            stringstream line(str);
            while(line >> word) {
                letter = word[0] - 'A'; 
                count++;
                if(letter >= num_vertices || letter < 0) {
                    if( count == 1 )
                        cerr << "Error: Starting vertex '" << word << "' on line " << line_num << " is not among valid values A-" << valid_range_value[num_vertices-1] << "." << endl; 
                    else
                        cerr << "Error: Ending vertex '" << word << "' on line " << line_num << " is not among valid values A-" << valid_range_value[num_vertices-1] << "." << endl; 
                    return false;
                }
                if( count == 2 )
                    break;
            } 
        }
        else 
            continue;
    } 
    return b_inrange;
}

int check_num_vertices(ifstream &text_file) {
    string str;
    int num_vertices = 0, line_num = 0;
 
    text_file.clear();
    text_file.seekg(0, ios::beg);
    while (getline(text_file, str)) {
        line_num++;
        if(str.size() > 0) {
            if(line_num == 1) {  
                num_vertices = 0;
                stringstream line_one(str);
                line_one >> num_vertices; 
                if(num_vertices < 1 || num_vertices > 26) {
                    cerr << "Error: Invalid number of vertices '" << str << "' on line 1." << endl;
                    num_vertices = 0;
                    break;
                }
                else {
                   break;
                }
            }
        }
        else {
           cerr << "Error: Invalid number of vertices '" << str << "' on line 1." << endl;
           num_vertices = 0;  
           break;
        }
    }
    return num_vertices;
}

int create_matrix(ifstream &text_file, int num_vertices, long *matrix) {
    string word, str;
    int ret = 0, line_num = 0, count = 0;
    
    for(int i = 0; i < num_vertices; i++) {
        for(int j = 0; j < num_vertices; j++) {
            if(i == j) { // diagnol
                *((matrix + i * num_vertices) + j) = 0;
            } else { // initiate to inf
                *((matrix + i * num_vertices) + j) = INF;
            }
        }
    }
    text_file.clear();
    text_file.seekg(0, ios::beg);
    int i = 0, j = 0;
    while(getline(text_file, str)) {
        line_num++;
        if(str.size() > 0) {
            if(line_num == 1) {
                continue;
            }
            count = 0;
            stringstream line(str);
            while(line >> word) {
                count++;
                if(count == 1) {
                    i = word[0] - 'A';
                } 
                else if(count == 2) {
                    j = word[0] - 'A';
                } else {
                    stringstream temp(word);
                    int x = 0;
                    temp >> x;
                    *((matrix + i*num_vertices) + j) = x; 
                }
            }
        } else {
            continue;
        }
    }
    return ret;
}


// Print path between two vertices
string print_path( long * const matrix, int i, int j, const int num_vertices, bool bTmp) {
    long value = 0;
    if(i == j) {
        string s(1, valid_range_value[i]); // convert one character to a string - 1 is the size 
        return s;
    }
    value = *((matrix + i*num_vertices) + j);
    if(value == INF) {
        string si(1, valid_range_value[i]);
        string sj(1, valid_range_value[j]);
        if(bTmp == false) {
            return si + " -> " + sj;
        } else {
            return sj;
        }
    } else {
        string si(1, valid_range_value[i]);
        for(int k = 0; k < 25; k++ ) {
            if(valid_range_value[k] == valid_range_value[value] ) {
             return print_path(matrix, i, k, num_vertices, bTmp) + " -> " + print_path(matrix, k, j, num_vertices, true);   
            }
        }
    }
    return "";
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long* const matrix, const string &label, const bool use_letters = false, const int num_vertices = 0) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = *((matrix + i*num_vertices) + j); 
            //long cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = *((matrix + i*num_vertices) + j); 
                //max_val = matrix[i][j];
            }
        }
    }

    int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(num_vertices), max_val));
    if(use_letters && num_vertices == 1) {
        cout << ' ';
        cout << ' ';
    }
    else
        cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    long cell_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            cell_val = *((matrix + i*num_vertices) + j); 
            if (cell_val == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(cell_val + 'A');
            } else {
                cout << cell_val;
            }
        }
        cout << endl;
    }  
    cout << endl;
}

// Print path and distance between two vertices
void display_path(long * const matrix, long * const inner_matrix, const int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = *((matrix + i*num_vertices) + j);
            if(cell == INF) {
                cout << valid_range_value[i] << " -> " << valid_range_value[j] << ", " << "distance: " << "infinity, path: none" << endl;
            }
            else { 
                cout << valid_range_value[i] << " -> " << valid_range_value[j] << ", " << "distance: " << cell << ", " << "path: ";
                cout << print_path(inner_matrix, i, j, num_vertices, false) << endl;   
            }
        }
    }
    return;
}

void floyd(long *matrix, long *inner_matrix, int num_vertices) {
    for(int k = 0; k < num_vertices; k++) {
        for(int i = 0; i < num_vertices; i++) {
            for(int j = 0; j < num_vertices; j++) {
                if(*((matrix + i*num_vertices) + j) > *((matrix + i*num_vertices) + k) + *((matrix + k*num_vertices) + j)) {
                    *((inner_matrix + i*num_vertices) + j) = k;
                }
                *((matrix + i*num_vertices) + j) = min(*((matrix + i*num_vertices) + j), 
                                                         *((matrix + i*num_vertices) + k) + *((matrix + k*num_vertices) + j));
            }
        }
    }
}



int main(int argc, char *argv[]) {

    if(argc != 2) {
        cout<<"Usage: ./shortestpaths <filename>"<<endl;
        return 1;
    }

    ifstream text_file(argv[1]);
    if(text_file.fail()) {
        cerr<<"Error: Cannot open file '"<<argv[1]<<"'."<<endl;
        return 1;
    }
    
    int ret = 0;
    int num_vertices = 0;
    long *matrix = NULL;
    long *inner_matrix = NULL;
    bool use_letters = false;
    string text;
    istringstream iss(text);

    num_vertices = check_num_vertices(text_file);
    if(num_vertices == 0) {
        ret = -1;
        goto _end;
    }

    else if(check_components(text_file) == false) {
        ret = -1;
        goto _end;
    }

    else if(check_vertex_range(text_file, num_vertices) == false) {
         ret = -1;
         goto _end;
    }

    else if(check_edge_weight(text_file) == false) {
        ret = -1;
        goto _end;
    }

    matrix = new long[num_vertices * num_vertices];
    if(matrix == NULL) {
         cerr << "Failed to allocate memory." << endl;
         ret = -1;
         goto _end;
    }
    ret = create_matrix(text_file, num_vertices, matrix);
    if(ret != 0) {
        goto _end;
    }
  
    inner_matrix = new long[num_vertices * num_vertices];
    if(inner_matrix == NULL) {
         cerr << "Failed to allocate memory." << endl;
         ret = -1;
         goto _end;
    }
    else {
     /* init to inf */
      for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            //if( i == j )
            //    *( (matrix + i*num_vertices) + j) = 0; 
            //else
                *((inner_matrix + i*num_vertices) + j) = INF; 
        }
      }       
    }

    use_letters = false;
    display_table((long *)matrix, "Distance matrix:", use_letters, num_vertices);

    floyd((long *)matrix, (long *)inner_matrix, num_vertices);
    display_table((long *)matrix, "Path lengths:", use_letters, num_vertices);

    use_letters = true;
    display_table((long *)inner_matrix, "Intermediate vertices:", use_letters, num_vertices);
    display_path((long *) matrix, (long *) inner_matrix, num_vertices);

    _end:
    if(matrix != NULL) {
        delete[] matrix;
    }
    delete[] inner_matrix;
    text_file.close();

    return ret;
}