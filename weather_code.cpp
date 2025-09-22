// PARNEET KAUR(2401360010) - THEORY ASSIGNMENT
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;


class WeatherRecord {
public:
    string date;
    string city;
    double temperature;

    WeatherRecord(string d = "", string c = "", double t = 0.0) {
        date = d;
        city = c;
        temperature = t;
    }
};


class WeatherDataStorage {
private:
    vector<string> cities;           
    vector<int> years;               
    vector<vector<double>> data;     
    double sentinel = -999;          

public:
    
    WeatherDataStorage(vector<string> c, vector<int> y) {
        cities = c;
        years = y;
        data.resize(years.size(), vector<double>(cities.size(), sentinel));
    }

    
    int getCityIndex(string city) {
        for (int i = 0; i < cities.size(); i++) {
            if (cities[i] == city) return i;
        }
        return -1;
    }

    
    int getYearIndex(int year) {
        for (int i = 0; i < years.size(); i++) {
            if (years[i] == year) return i;
        }
        return -1;
    }

    
    void populateArray(vector<WeatherRecord> records) {
        for (auto rec : records) {
            int year = stoi(rec.date.substr(6,4)); 
            insertRecord(rec.date, rec.city, year, rec.temperature);
        }
    }

    
    void insertRecord(string date, string city, int year, double temp) {
        int row = getYearIndex(year);
        int col = getCityIndex(city);
        if (row != -1 && col != -1) {
            data[row][col] = temp;
            cout << "Inserted: " << city << " " << year << " -> " << temp << "°C"<<endl;
        } else {
            cout << "Invalid city or year!"<<endl;
        }
    }

    
    void deleteRecord(string city, int year) {
        int row = getYearIndex(year);
        int col = getCityIndex(city);
        if (row != -1 && col != -1) {
            data[row][col] = sentinel;
            cout << "Deleted record for " << city << " in " << year << endl;
        } else {
            cout << "Invalid city or year!"<<endl;
        }
    }

    
    void retrieveRecord(string city, int year) {
        int row = getYearIndex(year);
        int col = getCityIndex(city);
        if (row != -1 && col != -1) {
            if (data[row][col] != sentinel)
                cout << "Temperature for " << city << " in " << year << " = " << data[row][col] << "°C"<<endl;
            else
                cout << "No data available for " << city << " in " << year << endl;
        } else {
            cout << "Invalid city or year!"<<endl;
        }
    }

    
    void rowMajorAccess() {
        for (int i = 0; i < years.size(); i++) {
            for (int j = 0; j < cities.size(); j++) {
                cout << "Year " << years[i] << ", City " << cities[j]
                     << " -> " << data[i][j] << "\n";
            }
        }
    }

    
    void columnMajorAccess() {
        for (int j = 0; j < cities.size(); j++) {
            for (int i = 0; i < years.size(); i++) {
                cout << "City " << cities[j] << ", Year " << years[i]
                     << " -> " << data[i][j] << endl;
            }
        }
    }

    
    void handleSparseData() {
        cout << "\nSparse Data Representation (non-missing records only):\n";
        for (int i = 0; i < years.size(); i++) {
            for (int j = 0; j < cities.size(); j++) {
                if (data[i][j] != sentinel) {
                    cout << "Year " << years[i] << ", City " << cities[j]
                         << " -> " << data[i][j] << "°C\n";
                }
            }
        }
    }

    
    void analyzeComplexity() {
        cout << endl<<"Time Complexity Analysis:  "<<endl;
        cout <<endl<< "insertRecord/deleteRecord/retrieveRecord: O(1)"<<endl;
        cout << "rowMajorAccess/columnMajorAccess: O(Y * C)"<<endl;
        cout <<endl<<"Space Complexity Analysis: "<<endl;
        cout << "2D array storage: O(Y * C)"<<endl;
    }

    
    void compareEfficiency() {
        auto start = chrono::high_resolution_clock::now();
        rowMajorAccess();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> rowTime = end - start;

        start = chrono::high_resolution_clock::now();
        columnMajorAccess();
        end = chrono::high_resolution_clock::now();
        chrono::duration<double> colTime = end - start;

        cout << endl<<"Row-major access time: " << rowTime.count() << " seconds"<<endl;
        cout << "Column-major access time: " << colTime.count() << " seconds"<<endl;
    }
};


int main() {
    vector<string> cityList = {"London", "Paris", "New York", "Tokyo", "Sydney", "Dubai"};
    vector<int> yearList = {2021, 2022, 2023, 2024};

    WeatherDataStorage storage(cityList, yearList);

    
    storage.insertRecord("01/01/2021", "London", 2021, 15.2);
    storage.insertRecord("01/01/2021", "Paris", 2021, 18.7);
    storage.insertRecord("01/01/2022", "New York", 2022, 10.4);
    storage.insertRecord("01/01/2022", "Tokyo", 2022, 22.9);
    storage.insertRecord("01/01/2023", "Sydney", 2023, 25.6);
    storage.insertRecord("01/01/2023", "Dubai", 2023, 33.5);
    storage.insertRecord("01/01/2024", "London", 2024, 16.8);
    storage.insertRecord("01/01/2024", "Tokyo", 2024, 23.7);

    cout << endl<<" Retrieve Example :  "<<endl;
    storage.retrieveRecord("Tokyo", 2024);
    storage.retrieveRecord("Paris", 2021);

    cout <<endl<<" Row Major Access :  "<<endl;
    storage.rowMajorAccess();

    cout << endl<<" Column Major Access :  "<<endl;
    storage.columnMajorAccess();

    cout << endl<<" Sparse Data :  "<<endl;
    storage.handleSparseData();

    cout << endl<<" Efficiency Comparison :  "<<endl;
    storage.compareEfficiency();

    cout << endl<< "  Complexity Analysis :   "<<endl;
    storage.analyzeComplexity();

    cout <<endl<< " Delete Example :  "<<endl;
    storage.deleteRecord("Tokyo", 2024);
    storage.retrieveRecord("Tokyo", 2024);

    return 0;
}
