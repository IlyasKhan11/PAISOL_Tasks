#include <iostream>
#include <vector>
#include <string>
#include <limits> 
using namespace std;

class MediaItem {
private:
    string title;
    int year;

public:
    MediaItem(string title, int year) : title(title), year(year) {}

    virtual ~MediaItem() = default;
    virtual string getInfo() const {
        return title + "( " + to_string(year) + ")";
    }
};

class Book : public MediaItem {
private:
    vector<string> authors;

public:
    Book(const string& title, int year, const vector<string>& authors)
        : MediaItem(title, year), authors(authors) {}

    string getInfo() const override {
        string info = MediaItem::getInfo() + " Book\n Authors: ";
        for (const string& auth : authors) {
            info += auth + ", ";
        }
        if (!authors.empty())
            info.pop_back(); // Remove last comma
        info += "\n";
        return info;
    }
    ~Book() override = default;
};

class Movie : public MediaItem {
private:
    string director;
    vector<string> actors;

public:
    Movie(const string& title, int year, const string& director, const vector<string>& actors)
        : MediaItem(title, year), director(director), actors(actors) {}

    string getInfo() const override {
        string info = MediaItem::getInfo() + " Movie\n Director: " + director + "\n Actors: ";
        for (const string& actor : actors) {
            info += actor + ", ";
        }
        info.pop_back();
        info += "\n";
        return info;
    }
};

class MusicAlbum : public MediaItem {
private:
    string artists;
    vector<string> songs;

public:
    MusicAlbum(const string& title, int year, const string& artists, const vector<string>& songs)
        : MediaItem(title, year), artists(artists), songs(songs) {}

    string getInfo() const override {
        string info = MediaItem::getInfo() + " Music Album\n Artists: " + artists + "\n Songs: ";
        for (const string& song : songs) {
            info += song + ", ";
        }
        info.pop_back();
        info += "\n";
        return info;
    }
};

class Library {
private:
    vector<MediaItem*> collection;

public:
    ~Library() {
        for (auto item : collection) {
            delete item;
        }
    }

    void add(MediaItem* item) {
        collection.push_back(item);
    }

    void Details() {
        cout << "MY LIBRARY" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        for (auto item : collection) {
            cout << item->getInfo() << endl; 
        }
        cout << "--------------------------------------------------------------------------------" << endl;
    }

    void remove( string& title) {
        auto it = collection.begin();
        while (it != collection.end()) {
            if ((*it)->getInfo().find(title) != string::npos) {
                delete *it;
                it = collection.erase(it);
                cout << "Item with title '" << title << "' removed successfully." << endl;
            } else {
                ++it;
            }
        }
    }

    vector<MediaItem*> searchTitle( string& title) {
        vector<MediaItem*> results;
        for (const MediaItem* item : collection) {
            if (item->getInfo().find(title) != string::npos) {
                results.push_back(const_cast<MediaItem*>(item)); // Remove the const
            }
        }
        return results;
    }

    // Function to add content based on user input
    void addContent() {
        int choice = 0;
        while (true) {
            cout << "Choose the type of content to add:" << endl;
            cout << "1. Book" << endl;
            cout << "2. Movie" << endl;
            cout << "3. Music Album" << endl;
            cout<<"--------------------------"<<endl;
            cout << "4. Search by title" << endl;
            cout << "5. Delete by title" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice (0-5): ";
            cin >> choice;

            if (choice == 1) {
                string title;
                int year;
                string author;
                vector<string> authors;

                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter year: ";
                cin >> year;
                cout << "Enter author names (comma-separated): ";
                cin.ignore();
                getline(cin, author);
                size_t pos = 0;
                string token;
                while ((pos = author.find(',')) != string::npos) {
                    token = author.substr(0, pos);
                    authors.push_back(token);
                    author.erase(0, pos + 1);
                }
                authors.push_back(author);
                add(new Book(title, year, authors));
            } else if (choice == 2) {
                string title;
                int year;
                string director;
                string actor;
                vector<string> actors;

                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter year: ";
                cin >> year;
                cout << "Enter director name: ";
                cin.ignore();
                getline(cin, director);
                cout << "Enter actor names (comma-separated): ";
                getline(cin, actor);
                size_t pos = 0;
                string token;
                while ((pos = actor.find(',')) != string::npos) {
                    token = actor.substr(0, pos);
                    actors.push_back(token);
                    actor.erase(0, pos + 1);
                }
                actors.push_back(actor);
                add(new Movie(title, year, director, actors));
            } else if (choice == 3) {
                string title;
                int year;
                string artist;
                string song;
                vector<string> songs;

                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter year: ";
                cin >> year;
                cout << "Enter artist name: ";
                cin.ignore();
                getline(cin, artist);
                cout << "Enter song names (comma-separated): ";
                getline(cin, song);
                size_t pos = 0;
                string token;
                while ((pos = song.find(',')) != string::npos) {
                    token = song.substr(0, pos);
                    songs.push_back(token);
                    song.erase(0, pos + 1);
                }
                songs.push_back(song);
                add(new MusicAlbum(title, year, artist, songs));
            } else if (choice == 4) {
                string title;
                cout << "Please enter the title to search: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                getline(cin, title);
                vector<MediaItem*> searchResults = searchTitle(title);
                if (searchResults.empty()) {
                    cout << "No items found with title '" << title << "'." << endl;
                } else {
                    cout << "Search Results:" << endl;
                    for (const auto& item : searchResults) {
                        cout << item->getInfo() << endl;
                    }
                }
            } else if (choice == 5) {
                string title;
                cout << "Please enter the title to delete: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                getline(cin, title);
                remove(title);
            } else if (choice == 0) {
                cout << "Exiting..." << endl;
                break;
            } else {
                cout << "Invalid choice!" << endl;
            }
        }
    }
};

int main() {
    Library MyCollection;

    MyCollection.add(new Book("48 laws of Power", 1990, {"Robert Greene"}));
    MyCollection.add(new Movie("Puss in Books", 2022, "Someone", {"Cat", "Death Fox"}));
    MyCollection.add(new MusicAlbum("Thriller", 1982, "Michael Jackson", {"Billie Jean", "Beat It", "Thriller"}));

    MyCollection.Details();

    // Adding content based on user input
    MyCollection.addContent();

    MyCollection.Details();

    return 0;
}
