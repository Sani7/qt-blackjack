#include "playwindow.hpp"
#include "ui_playwindow.h"

#define QD qDebug() << "File:" << __FILE__ << "Function:" << __PRETTY_FUNCTION__ << "Line:" << __LINE__ << "=>"

playWindow::playWindow(QWidget *parent) : QMainWindow(parent),
      ui(new Ui::playWindow),
      standarPalette{qApp->palette()},
      darkPalette{},
      cardToImg{
          {Card(Card::Rank::ACE, Card::Suit::CLUBS),      "AC"},
          {Card(Card::Rank::TWO, Card::Suit::CLUBS),      "2C"},
          {Card(Card::Rank::THREE, Card::Suit::CLUBS),    "3C"},
          {Card(Card::Rank::FOUR, Card::Suit::CLUBS),     "4C"},
          {Card(Card::Rank::FIVE, Card::Suit::CLUBS),     "5C"},
          {Card(Card::Rank::SIX, Card::Suit::CLUBS),      "6C"},
          {Card(Card::Rank::SEVEN, Card::Suit::CLUBS),    "7C"},
          {Card(Card::Rank::EIGHT, Card::Suit::CLUBS),    "8C"},
          {Card(Card::Rank::NINE, Card::Suit::CLUBS),     "9C"},
          {Card(Card::Rank::TEN, Card::Suit::CLUBS),      "10C"},
          {Card(Card::Rank::JACK, Card::Suit::CLUBS),     "JC"},
          {Card(Card::Rank::QUEEN, Card::Suit::CLUBS),    "QC"},
          {Card(Card::Rank::KING, Card::Suit::CLUBS),     "KC"},
          {Card(Card::Rank::ACE, Card::Suit::DIAMONDS),   "AD"},
          {Card(Card::Rank::TWO, Card::Suit::DIAMONDS),   "2D"},
          {Card(Card::Rank::THREE, Card::Suit::DIAMONDS), "3D"},
          {Card(Card::Rank::FOUR, Card::Suit::DIAMONDS),  "4D"},
          {Card(Card::Rank::FIVE, Card::Suit::DIAMONDS),  "5D"},
          {Card(Card::Rank::SIX, Card::Suit::DIAMONDS),   "6D"},
          {Card(Card::Rank::SEVEN, Card::Suit::DIAMONDS), "7D"},
          {Card(Card::Rank::EIGHT, Card::Suit::DIAMONDS), "8D"},
          {Card(Card::Rank::NINE, Card::Suit::DIAMONDS),  "9D"},
          {Card(Card::Rank::TEN, Card::Suit::DIAMONDS),   "10D"},
          {Card(Card::Rank::JACK, Card::Suit::DIAMONDS),  "JD"},
          {Card(Card::Rank::QUEEN, Card::Suit::DIAMONDS), "QD"},
          {Card(Card::Rank::KING, Card::Suit::DIAMONDS),  "KD"},
          {Card(Card::Rank::ACE, Card::Suit::HEARTS),     "AH"},
          {Card(Card::Rank::TWO, Card::Suit::HEARTS),     "2H"},
          {Card(Card::Rank::THREE, Card::Suit::HEARTS),   "3H"},
          {Card(Card::Rank::FOUR, Card::Suit::HEARTS),    "4H"},
          {Card(Card::Rank::FIVE, Card::Suit::HEARTS),    "5H"},
          {Card(Card::Rank::SIX, Card::Suit::HEARTS),     "6H"},
          {Card(Card::Rank::SEVEN, Card::Suit::HEARTS),   "7H"},
          {Card(Card::Rank::EIGHT, Card::Suit::HEARTS),   "8H"},
          {Card(Card::Rank::NINE, Card::Suit::HEARTS),    "9H"},
          {Card(Card::Rank::TEN, Card::Suit::HEARTS),     "10H"},
          {Card(Card::Rank::JACK, Card::Suit::HEARTS),    "JH"},
          {Card(Card::Rank::QUEEN, Card::Suit::HEARTS),   "QH"},
          {Card(Card::Rank::KING, Card::Suit::HEARTS),    "KH"},
          {Card(Card::Rank::ACE, Card::Suit::SPADES),     "AS"},
          {Card(Card::Rank::TWO, Card::Suit::SPADES),     "2S"},
          {Card(Card::Rank::THREE, Card::Suit::SPADES),   "3S"},
          {Card(Card::Rank::FOUR, Card::Suit::SPADES),    "4S"},
          {Card(Card::Rank::FIVE, Card::Suit::SPADES),    "5S"},
          {Card(Card::Rank::SIX, Card::Suit::SPADES),     "6S"},
          {Card(Card::Rank::SEVEN, Card::Suit::SPADES),   "7S"},
          {Card(Card::Rank::EIGHT, Card::Suit::SPADES),   "8S"},
          {Card(Card::Rank::NINE, Card::Suit::SPADES),    "9S"},
          {Card(Card::Rank::TEN, Card::Suit::SPADES),     "10S"},
          {Card(Card::Rank::JACK, Card::Suit::SPADES),    "JS"},
          {Card(Card::Rank::QUEEN, Card::Suit::SPADES),   "QS"},
          {Card(Card::Rank::KING, Card::Suit::SPADES),    "KS"}},
      deck{std::make_unique<Deck>()},
      dealer{std::make_unique<Player>()},
      player{std::make_unique<Player>()},
      turnCount{0},
      player_wins{0},
      computer_wins{0}
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(164, 166, 168));
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(164, 166, 168));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(164, 166, 168));
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(164, 166, 168));
    darkPalette.setColor(QPalette::Disabled, QPalette::Base, QColor(68, 68, 68));
    darkPalette.setColor(QPalette::Disabled, QPalette::Window, QColor(68, 68, 68));
    darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(68, 68, 68));

    countToPlayerLabel = {
        ui->card1Label, ui->card2Label, ui->card3Label, ui->card4Label, ui->card5Label, ui->card6Label, ui->card7Label, ui->card8Label, ui->card9Label, ui->card10Label
    };

    countToDealerLabel = {
        ui->card10Label_2, ui->card9Label_2, ui->card8Label_2, ui->card7Label_2, ui->card6Label_2, ui->card5Label_2, ui->card4Label_2, ui->card3Label_2, ui->card2Label_2, ui->card1Label_2
    };

    qApp->setStyle("Fusion");
    qApp->setPalette(darkPalette);

    deck->shuffledeck();

    connect(ui->twistButton, &QPushButton::clicked, this, [=]
            { playerTurn(); });
    connect(ui->stickButton, &QPushButton::clicked, this, [=]
            {
                // To prevent users from activating function before the function ending.
                this->setEnabled(false);
                ui->playagainButton->setEnabled(true);
                ui->twistButton->setEnabled(false);
                ui->stickButton->setEnabled(false);

                //Generating Computer score
                computerTurn();
            });

    connect(ui->playagainButton, &QPushButton::clicked, this, [=]{reset();});
}

void playWindow::playerTurn(void)
{
    if (turnCount > 9)
        return;
    player->addCard(deck->drawCard());

    QPixmap img = QPixmap(":/images/cards/" + cardToImg[player->getLastCard()] + ".png");

    img = img.scaled(ui->card10Label->size().width(), ui->card10Label->size().height(), Qt::KeepAspectRatio);

    countToPlayerLabel[turnCount]->setPixmap(img);

    ui->playertotalLabel->setText("Total: " + QString::number(player->getHandValue()));

    turnCount++;

           // if player bust
    if (player->getHandValue() > 21)
    {
        ui->twistButton->setEnabled(false);
        ui->stickButton->setEnabled(false);

               // Generating Computer score
        computerTurn();
        return;
    }
    if (player->getHandValue() > 15)
    {
        ui->stickButton->setEnabled(true);
        return;
    }
    if (player->getHandValue() <= 15)
    {
        ui->stickButton->setEnabled(false);
        ui->playagainButton->setEnabled(true);
    }
}

void playWindow::computerTurn(void)
{
    QPixmap win(":/images/win.png");
    QPixmap lose(":/images/lose.png");
    QPixmap draw(":/images/draw.png");

    turnCount = 0;
    while (dealer->getHandValue() < 18){
        dealer->addCard(deck->drawCard());
        QPixmap img = QPixmap(":/images/cards/" + cardToImg[dealer->getLastCard()] + ".png");
        img = img.scaled(ui->card10Label->size().width(), ui->card10Label->size().height(), Qt::KeepAspectRatio);

        ui->computerScoreLabel->setText("Computer: " + QString::number(dealer->getHandValue()));

        countToDealerLabel[turnCount]->setPixmap(img);

        turnCount++;
    }

    int8_t winner = calculate_winner(player.get(), dealer.get());
    if (winner < 0)
    {
        ui->outcomeLabel->setPixmap(lose);;
        computer_wins++;
    }

    if (winner == 0)
    {
        ui->outcomeLabel->setPixmap(draw);
    }

    if (winner > 0)
    {
        ui->outcomeLabel->setPixmap(win);
        player_wins++;
    }

    ui->statusbar->showMessage("Gamescore Player: " + QString::number(player_wins) + " - " + "Computer: " + QString::number(computer_wins) + " - Win Percentage: " + QString::number(static_cast<double>(player_wins) / static_cast<double>(player_wins + computer_wins) * 100) + "%");
    this->setEnabled(true);
}

void playWindow::reset(void)
{
    deck.reset(new Deck());
    player.reset(new Player());
    dealer.reset(new Player());

    deck->shuffledeck();

           //Clear Labels and Variables
    turnCount = 0;

    ui->playertotalLabel->setText("Total: " + QString::number(0));

    ui->twistButton->setEnabled(true);
    ui->playagainButton->setEnabled(false);
    ui->stickButton->setEnabled(false);
    ui->outcomeLabel->clear();
    ui->computerScoreLabel->setText("Computer: " + QString::number(0));

           // Clear Cards from player table
    ui->card1Label->clear();
    ui->card2Label->clear();
    ui->card3Label->clear();
    ui->card4Label->clear();
    ui->card5Label->clear();
    ui->card6Label->clear();
    ui->card8Label->clear();
    ui->card9Label->clear();
    ui->card10Label->clear();

    ui->card10Label_2->clear();
    ui->card9Label_2->clear();
    ui->card8Label_2->clear();
    ui->card7Label_2->clear();
    ui->card6Label_2->clear();
    ui->card5Label_2->clear();
    ui->card4Label_2->clear();
    ui->card3Label_2->clear();
    ui->card2Label_2->clear();
    ui->card1Label_2->clear();
}

int8_t playWindow::calculate_winner(Player* player, Player* dealer)
{
    // if dealer and player lose, dealer wins
    if (dealer->getHandValue() > 21 && player->getHandValue() > 21)
    {
        return 0;
    }

    // if same score, draw
    if (dealer->getHandValue() == player->getHandValue()){
        return 0;
    }

           // if dealer went bust, player wins
    if (dealer->getHandValue() > 21)
    {
        return 1;
    }

           // if player went bust, dealer wins
    if (player->getHandValue() > 21)
    {
        return -1;
    }

           // player and dealer both have less then 21
           // hence compare the values
    return player->getHandValue() > dealer->getHandValue() ? 1 : -1;
}

playWindow::~playWindow()
{
    delete ui;
}
