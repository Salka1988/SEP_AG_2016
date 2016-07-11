#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

enum ERROR {
  SUCCESS,
  USER_NOT_FOUND,
  USER_ALREADY_JOINED,
  ROOM_ALREADY_EXISTS,
  ROOM_DOES_NOT_EXIST
};

void printErr(ERROR err) {
  switch(err) {
    case USER_NOT_FOUND:
      cout << "User not found!" << endl;
      break;
    case USER_ALREADY_JOINED:
      cout << "User already joined!" << endl;
      break;
    case ROOM_ALREADY_EXISTS:
      cout << "Room already exists!" << endl;
      break;
    case ROOM_DOES_NOT_EXIST:
      cout << "Room does not exist!" << endl;
      break;
    default:
      break;
  }
}

class User {
private:
  string name_;
public:
  User(string name) : name_(name) {};
  string getName() const { return name_; };
};

class ChatRoom {
private:
  string name_;
  vector<string> messages_;
  vector<User> userList_;
public:
  ChatRoom(string name) : name_(name) {};
  ERROR writeMessageByUser(const User &user, string message) {
      cout << name_ << endl;
      messages_.push_back(user.getName() + ": " + message);
      for(auto const &msg : messages_) {
        cout << msg << endl;
      }
      
      return SUCCESS;
  };
  
  bool hasUser(const User &user) {
    return find_if(userList_.begin(), userList_.end(), 
      [&](const User &u) -> bool { return u.getName() == user.getName(); }) != userList_.end();
  }
  
  void addUser(const User &user) {
    userList_.push_back(user);
  }
  string getName() const { return name_; };
};

// Helper
ChatRoom *findUserInChatRooms(vector<ChatRoom*> &chatRooms, const User &user) {
  ChatRoom *chatRoom = nullptr;
  for(auto chatRoomTmp : chatRooms) {
    if(chatRoomTmp->hasUser(user)) {
      chatRoom = chatRoomTmp;
    }
  }
  return chatRoom;
}


int main() {
    vector<ChatRoom*> chatRooms;
    
    while(true) {
        cout << "> ";
        string command;
        
        if(!getline(cin, command))
          break;

        if (command == "") continue;
        istringstream iss(command);
        vector <string> tokens{istream_iterator < string > {iss}, istream_iterator < string > {}};
        
        // QUIT
        if(tokens[0] == "quit") {
           break;
        
        // CREATE
        } else if(tokens[0] == "create" && tokens.size() == 2) {
          if(find_if(chatRooms.begin(), chatRooms.end(), 
                  [&](const ChatRoom *c) -> bool { return c->getName() == tokens[1]; }) != chatRooms.end()) {
            printErr(ROOM_ALREADY_EXISTS);
          } else chatRooms.push_back(new ChatRoom(tokens[1]));
          
        // SHOW
        } else if(tokens[0] == "show" && tokens.size() == 1) {
          for(auto chatRoom : chatRooms) {
            cout << chatRoom->getName() << endl;
          }
          
        // JOIN
        } else if(tokens[0] == "join" && tokens.size() == 3) {
          ChatRoom *chatRoom = nullptr;
          for(auto chatRoomTmp : chatRooms) {
            if(chatRoomTmp->getName() == tokens[1])
              chatRoom = chatRoomTmp;
          }
          
          if(chatRoom == nullptr) {
            printErr(ROOM_DOES_NOT_EXIST);
            continue;
          }
          if(chatRoom->hasUser(User(tokens[2]))) {
            printErr(USER_ALREADY_JOINED);
            continue;
          }
          chatRoom->addUser(User(tokens[2]));
          
        // WRITE
        } else if(tokens[0] == "write" && tokens.size() >= 3) {
          // is this user assigned to a chatRoom ?
          ChatRoom *chatRoomToSearch = findUserInChatRooms(chatRooms, User(tokens[1]));
          if(chatRoomToSearch == nullptr) {
            printErr(USER_NOT_FOUND);
          } else {
            // concatenate vector string
            string result;
            std::for_each(tokens.begin() + 2, tokens.end(), [&](const std::string &part){ result += (part + " "); });
            chatRoomToSearch->writeMessageByUser(User(tokens[1]), result);
          }
        }
    }
    
    for(auto chatRoom : chatRooms) {
      delete chatRoom;   
    }
    
    return 0;
}
