Task Scheduler

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib> // for system()
#include <ctime>

using namespace std;

// Your task function — customize this!
void runTask() {
    time_t now = time(0);
    cout << "Running task at: " << ctime(&now) << endl;

    // Example: Launch Notepad (Windows) or any command
    // system("notepad.exe");

    // Example: Run your own script or executable
    // system("C:\\Path\\To\\your_script.bat");
    // system("python your_script.py");

    // Just for demo
    cout << "Task completed.\n\n";
}

int main() {
    int intervalSeconds;

    cout << "Enter interval in seconds to run the task: ";
    cin >> intervalSeconds;

    while (true) {
        runTask();
        this_thread::sleep_for(chrono::seconds(intervalSeconds));
    }

    return 0;
}

Blockchain 

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>
#include <functional> // for std::hash

using namespace std;

// Block class
class Block {
public:
    int index;
    string data;
    string prevHash;
    string blockHash;  // <-- changed variable name from 'hash' to avoid conflict
    long timestamp;
    int nonce;

    Block(int idx, string d, string prevHash)
        : index(idx), data(d), prevHash(prevHash), timestamp(time(0)), nonce(0) {
        blockHash = calculateHash();
    }

    string calculateHash() const {
        stringstream ss;
        ss << index << data << prevHash << timestamp << nonce;
        return to_string(std::hash<string>{}(ss.str()));
    }

    void mineBlock(int difficulty) {
        string target(difficulty, '0');
        while (blockHash.substr(0, difficulty) != target) {
            nonce++;
            blockHash = calculateHash();
        }
        cout << "✅ Block mined: " << blockHash << endl;
    }
};

// Blockchain class
class Blockchain {
public:
    vector<Block> chain;
    int difficulty;

    Blockchain(int diff) {
        difficulty = diff;
        chain.push_back(createGenesisBlock());
    }

    Block createGenesisBlock() {
        return Block(0, "Genesis Block", "0");
    }

    Block getLatestBlock() {
        return chain.back();
    }

    void addBlock(string data) {
        Block newBlock(chain.size(), data, getLatestBlock().blockHash);
        cout << "🔨 Mining block " << newBlock.index << "...\n";
        newBlock.mineBlock(difficulty);
        chain.push_back(newBlock);
    }

    void displayChain() {
        for (const Block& block : chain) {
            cout << "\n🧱 Block " << block.index
                 << "\nData: " << block.data
                 << "\nTimestamp: " << block.timestamp
                 << "\nPrevHash: " << block.prevHash
                 << "\nHash: " << block.blockHash
                 << "\nNonce: " << block.nonce
                 << "\n-----------------------------";
        }
    }
};

// Main
int main() {
    Blockchain myBlockchain(4); // Difficulty level

    myBlockchain.addBlock("Ashish pays Bob 10 coins");
    myBlockchain.addBlock("Bob pays Charlie 5 coins");

    myBlockchain.displayChain();

    return 0;
}
