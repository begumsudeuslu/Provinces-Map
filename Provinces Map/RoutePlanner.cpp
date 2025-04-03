#include "RoutePlanner.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {

    // TO DO:

    // Load map data from file
    map.loadDistanceData(distance_data);

    // Mark all provinces as unvisited initially
    map.resetVisited();

    // Load priority provinces
    loadPriorityProvinces(priority_data);

    // Load restricted provinces
    loadWeatherRestrictedProvinces(restricted_data);
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    // TODO: Your code here
    std::ifstream file(filename);
    if (!file.is_open())  {
        std::cerr << "Error priority_provinces.txt cannot open." << std::endl;
        return;
    }

    std::string line;
    int index = 0;

    while(getline(file, line))  {
        size_t openBraketIndex = line.find('(');
        size_t closeBraketIndex = line.find(')');

        //std::string provinceName = line.substr(0, openBraketIndex - 1);
        int provinceIndex = std::stoi(line.substr(openBraketIndex + 1, closeBraketIndex-openBraketIndex-1));

        if(index < MAX_PRIORITY_PROVINCES)  {
            priorityProvinces[index] = provinceIndex;
            index++;
        }  else  {
            std::cerr << "warning maximum priortiy provinces exceed." << std::endl;
            break;
        }
        
    }
    numPriorityProvinces = index;
    file.close();
}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    // TODO: Your code here
    std::ifstream file(filename);
    if(!file.is_open())  {
        std::cerr << "Error weather_restricted_provinces.txt couldnt open." << std::endl;
        return;
    }

    std::string line;
    int index = 0;

    while(getline(file, line))  {
        size_t openBraketIndex = line.find('(');
        size_t closeBraketIndex = line.find(')');

        //std::string provinceName = line.substr(0, openBraketIndex - 1);
        int provinceIndex = std::stoi(line.substr(openBraketIndex + 1, closeBraketIndex-openBraketIndex-1));
        
        if(index < MAX_WEATHER_RESTRICTED_PROVINCES)  {
            weatherRestrictedProvinces[index] = provinceIndex;
            index++;
        }  else  {
            std::cerr << "warning maximum priortiy provinces exceed." << std::endl;
            break;
        }
        
    }
    numWeatherRestrictedProvinces= index;
    file.close();
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    // TODO: Your code here
    for (int i = 0; i <numPriorityProvinces; ++i)  {
        if (priorityProvinces[i] == province)  {
            return true;
        }
    }
    return false;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    // TODO: Your code here
    for (int i = 0; i < numWeatherRestrictedProvinces; ++i)  {
        if (weatherRestrictedProvinces[i] == province)  {
            return true;
        }
    }
    return false;
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    // TODO: Your code here
    map.visited[startingCity] = true;
    stack.push(startingCity);
    route.push_back(startingCity);
    totalDistanceCovered = 0;

    while(!stack.isEmpty() && !isExplorationComplete())  {
        int curProvince = stack.pop();
        exploreFromProvince(curProvince);
    }

    displayResults();

}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    // TODO: Your code here
    enqueueNeighbors(province);

    while(!queue.isEmpty())  {
        int neighbor = queue.dequeue();

        if(isWeatherRestricted(neighbor))  {
            std::cout << "Province " << cities[neighbor] << " is weather-restricted. Skipping.\n";
            continue;
        }

        map.visited[neighbor] = true;
        stack.push(neighbor);
        route.push_back(neighbor);
        totalDistanceCovered+=map.getDistance(province, neighbor);
        
    }

    if(stack.isEmpty() && !isExplorationComplete())  {
        backtrack();
    }

}

void RoutePlanner::enqueueNeighbors(int province) {
    // TO DO: Enqueue priority & non-priority neighbors to the queue according to given constraints
    for(int neighbor=0; neighbor < MAX_SIZE; ++neighbor)   {

        if(map.isWithinRange(province, neighbor, maxDistance) && !map.isVisited(neighbor) && !isWeatherRestricted(neighbor))  {
            
            if(isPriorityProvince(neighbor))    {
                queue.enqueue(neighbor);
            } else   {
                queue.enqueue(neighbor);
            }
        }
    }
}

void RoutePlanner::backtrack() {
    // If you reach a dead-end province 
    // TODO: Your code here
    if (stack.isEmpty())  {
        return;
    }

    int lastProvince = stack.peek();
    stack.pop();
    
    map.visited[lastProvince]=false;

    if(!stack.isEmpty())  {
        int preProvince = stack.peek();
        totalDistanceCovered -= map.getDistance(preProvince, lastProvince);
    }

    if(!route.empty() && route.back()==lastProvince)   {
        route.pop_back();
    }

    /*    // Re-enqueue neighbors of the previous province if necessary
    if (!queue.isEmpty()) {
        enqueueNeighbors(stack.peek());
    */
}

bool RoutePlanner::isExplorationComplete() const {
    // TODO: Your code here
    if (queue.isEmpty() && stack.isEmpty())   {
        return true;
    }

    for (int province : route )   {
        for (int neighbor=0; neighbor <MAX_SIZE; ++neighbor)    {
            if (neighbor == province)   {
                continue;
            }
            if (!map.isVisited(neighbor) && map.isWithinRange(province, neighbor, maxDistance) && !isWeatherRestricted(neighbor))    {
                return false;
            }
        }
    }
    return false;
}

void RoutePlanner::displayResults() const {
    // TODO: Your code here

    // Display "Journey Completed!" message
    std::cout << "----------------------------\n";
    std::cout << "Journey Completed!\n";
    std::cout << "----------------------------\n" ;

    // Display the total number of provinces visited
    std::cout << "Total Number of Provinces Visited: " << route.size() << std::endl;

    // Display the total distance covered
    std::cout << " Total Distance Covered: " << totalDistanceCovered << " km\n";

    // Display the route in the order visited
    std::cout << "Route Taken:\n";
    for (int i = 0; i < route.size(); ++i) {
        std::cout << cities[route[i]];
        if (i < route.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    // Priority Province Summary
    int visitedPriorityProvinces=0;
    std::cout << "Priority Provinces Status:\n";
    for (int i = 0; i < numPriorityProvinces; ++i) {
        std::cout << "- " << cities[priorityProvinces[i]] << " (";
        if(map.isVisited(priorityProvinces[i]))  {
            std::cout << "Visited)\n";
            visitedPriorityProvinces++;
        }  else  {
            std::cout << "Not Visited)\n";
        }
    }


    std::cout << "Total Priority Provinces Visited: " << visitedPriorityProvinces << " out of " << numPriorityProvinces << std::endl;
    if (visitedPriorityProvinces == numPriorityProvinces) {
        std::cout << "Success: All priority provinces were visited.\n";
    } else {
        std::cout << "Warning: Not all priority provinces were visited.\n";
    }
}
