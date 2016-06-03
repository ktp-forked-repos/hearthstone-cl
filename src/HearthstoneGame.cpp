#include "HearthstoneGame.h"

using namespace HearthstoneCL;

HearthstoneGame::HearthstoneGame() {}
HearthstoneGame::~HearthstoneGame() {}

void HearthstoneGame::showUsage() {

  if (suppressUsageMessage) {
    return;
  }

  using std::cerr;
  using std::endl;

  cerr << "Usage: hearthstone_cl [-D] [--strict-decks=false] "
      "/path/to/deck1.txt /path/to/deck2.txt"
  << endl;
  cerr << "       (deck files go in \"decks\" directory)" << endl;
  cerr << "       -D = debug mode" << endl;
  cerr << "       --strict-decks=false = allow any deck of 30 cards, no "
      "restrictions"
  << endl;
  cerr << "       --strict-decks=true = (default) legal deck of 30 cards"
  << endl;
}

bool HearthstoneGame::setupFromCommandLineOptions(const int argc,
                                                  char *argv[]) {

  using std::string;

  bool cmdDebugMode = false;
  bool cmdStrictDecks = true;
  string deck1;
  string deck2;
  int optionalArgCount{0};
  const int minArgCount{3};

  if (argc < minArgCount) {
    showUsage();
    return false;
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-D") == 0) {
      optionalArgCount++;
      cmdDebugMode = true;
    } else if (strcmp(argv[i], "--strict-decks=false") == 0) {
      optionalArgCount++;
      cmdStrictDecks = false;
    } else if (strcmp(argv[i], "--strict-decks=true") == 0) {
      optionalArgCount++;
      cmdStrictDecks = true;
    }
  }

  if (optionalArgCount + minArgCount < argc) {
    showUsage();
    return false;
  }

  // always the last 2 arguments
  deck1 = argv[optionalArgCount + 1];
  deck2 = argv[optionalArgCount + 2];

  args.debugMode = cmdDebugMode;
  args.strictDecks = cmdStrictDecks;
  args.deck1Name = deck1;
  args.deck2Name = deck2;

  if (args.debugMode) {
    enableDebugMode();
  }
  if (not args.strictDecks) {
    disableStrictDecks();
  }
  setDeck1(args.deck1Name);
  setDeck2(args.deck2Name);

  return true;
}

void HearthstoneGame::suppressUsage() {
  suppressUsageMessage = true;
}

void HearthstoneGame::enableDebugMode() { debugMode = true; }

void HearthstoneGame::disableStrictDecks() { strictDeckMode = false; }

void HearthstoneGame::setDeck1(const std::string &deck) {
  setupPlayer(deck, player1);
}

void HearthstoneGame::setDeck2(const std::string &deck) {
  setupPlayer(deck, player2);
}

void HearthstoneGame::setupPlayer(const std::string deckFilePath,
                                  Player &player) {
  Deck deck;
  if (debugMode) {
    deck.enableDebugMode();
  }
  if (not strictDeckMode) {
    deck.disableStrictMode();
  }

  deck.loadDeckFromFile(deckFilePath);

  // player.deck
}

void HearthstoneGame::start() {
  // make sure there is deck1
  // make sure there is deck2

  std::cout << "Here we go." << std::endl;

  // start the game
}

// void HearthstoneGame::deckCheck() {
//
//    const int maxDeckSize {30};
//    int maxPerLegendary {1};
//    int maxPerNonLegendary {2};
//
//    if (not strictDecks) {
//        maxPerLegendary = maxDeckSize;
//        maxPerNonLegendary = maxDeckSize;
//    }
//
//    return true;
//}
