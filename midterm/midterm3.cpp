#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

typedef long long ll;
using namespace std;

struct song{
    string track;
    string artist;
    string streams;
    bool exp;
};

void getInfo(string line, string &track, string &artist, string &streams, string &exp){
    int n = line.size();
    int* comma = new int[3];
    int k = 2;
    for (int i = n - 1; i >= 0; i--){
        if (line[i] == ','){
            comma[k] = i; k--;
        }
        if (k < 0) break;
    }
    track = line.substr(1, comma[0] - 2);
    artist = line.substr(comma[0] + 2, comma[1] - comma[0] - 3);
    streams = line.substr(comma[1] + 1, comma[2] - comma[1] - 1);
    exp = line.substr(comma[2] + 1, 1);
}

void readFile(vector<song>& songs, string &header){
    ifstream file("MostStreamedSpotifySongs2024.txt");
    string line;
    getline(file, line);
    header = line;
    while(getline(file, line)){
        if (line.empty()) continue;
        song newSong;
        string track, artist, streams, exp;
        getInfo(line, track, artist, streams, exp);
        newSong.track = track;
        newSong.artist = artist;
        newSong.streams = streams;
        if (stoi(exp) == 1) newSong.exp = true;
        else newSong.exp = false;
        songs.push_back(newSong);
    }
}

void sortSongs(vector<song> &songs){
    ll n = songs.size();
    for (ll i = 0; i < n; i++){
        ll maxStreams = 0;
        ll maxID = 0;
        for (ll j = i; j < n; j++){
            if (stoll(songs[j].streams) > maxStreams){
                maxStreams = stoll(songs[j].streams);
                maxID = j;
            }
        }
        swap(songs[i], songs[maxID]);
    }
}

int findArtist(vector<pair<string, int>> &artistSongs, string artist){
    for (int i = 0; i < artistSongs.size(); i++){
        if (artistSongs[i].first == artist) return i;
    }
    return -1;
}

int main(){
    vector<song> songs;
    string header;
    readFile(songs, header);
    freopen("filtered_songs.txt", "w", stdout);
    cout << "Track,Artist,Spotify Streams\n";
    int n = songs.size();
    vector<song> songs_filtered;
    for (int i = 0; i < n; i++){
        song now = songs[i];
        if (now.exp) continue;
        cout << "\"" << now.track << "\",\"" << now.artist << "\"," << now.streams << "\n";
        songs_filtered.push_back(now);
        // cout << now.track << " " << now.artist << " " << now.streams << "\n";
    }
    songs = songs_filtered;
    freopen("CON", "w", stdout);
    
    sortSongs(songs);
    cout << "Top 5 songs by streams:\n";
    for (int i = 0; i < 5; i++){
        cout << i+1 << ". " << songs[i].track << " by " << songs[i].artist 
        << " with " << songs[i].streams << " streams.\n";
    }

    vector<pair<string, int>> artistSongs;
    for (int i = 0; i < n; i++){
        song now = songs[i];
        int id = findArtist(artistSongs, now.artist);
        if (id == -1){
            artistSongs.push_back({now.artist, 1});
        } else {
            artistSongs[id].second++;
        }
    }
    int maxSongs = 0;
    int artistOfYear = 0;
    for (int i = 0; i < artistSongs.size(); i++){
        if (artistSongs[i].second > maxSongs){
            maxSongs = artistSongs[i].second;
            artistOfYear = i;
        }
    }
    cout << "Artist of the year: " << artistSongs[artistOfYear].first 
    << " with " << artistSongs[artistOfYear].second << " songs.\n";
}