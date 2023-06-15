#include "playwindow.hpp"
#include "ui_playwindow.h"

#define QD qDebug() << "File:" << __FILE__ << "Function:" << __PRETTY_FUNCTION__ << "Line:" << __LINE__ << "=>"

playWindow::playWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::playWindow)
{
    ui->setupUi(this);

    cardToImg = {
        {Card(Card::Rank::ACE, Card::Suit::CLUBS), "AC"},
        {Card(Card::Rank::TWO, Card::Suit::CLUBS), "2C"},
        {Card(Card::Rank::THREE, Card::Suit::CLUBS), "3C"},
        {Card(Card::Rank::FOUR, Card::Suit::CLUBS), "4C"},
        {Card(Card::Rank::FIVE, Card::Suit::CLUBS), "5C"},
        {Card(Card::Rank::SIX, Card::Suit::CLUBS), "6C"},
        {Card(Card::Rank::SEVEN, Card::Suit::CLUBS), "7C"},
        {Card(Card::Rank::EIGHT, Card::Suit::CLUBS), "8C"},
        {Card(Card::Rank::NINE, Card::Suit::CLUBS), "9C"},
        {Card(Card::Rank::TEN, Card::Suit::CLUBS), "10C"},
        {Card(Card::Rank::JACK, Card::Suit::CLUBS), "JC"},
        {Card(Card::Rank::QUEEN, Card::Suit::CLUBS), "QC"},
        {Card(Card::Rank::KING, Card::Suit::CLUBS), "KC"},
        {Card(Card::Rank::ACE, Card::Suit::DIAMONDS), "AD"},
        {Card(Card::Rank::TWO, Card::Suit::DIAMONDS), "2D"},
        {Card(Card::Rank::THREE, Card::Suit::DIAMONDS), "3D"},
        {Card(Card::Rank::FOUR, Card::Suit::DIAMONDS), "4D"},
        {Card(Card::Rank::FIVE, Card::Suit::DIAMONDS), "5D"},
        {Card(Card::Rank::SIX, Card::Suit::DIAMONDS), "6D"},
        {Card(Card::Rank::SEVEN, Card::Suit::DIAMONDS), "7D"},
        {Card(Card::Rank::EIGHT, Card::Suit::DIAMONDS), "8D"},
        {Card(Card::Rank::NINE, Card::Suit::DIAMONDS), "9D"},
        {Card(Card::Rank::TEN, Card::Suit::DIAMONDS), "10D"},
        {Card(Card::Rank::JACK, Card::Suit::DIAMONDS), "JD"},
        {Card(Card::Rank::QUEEN, Card::Suit::DIAMONDS), "QD"},
        {Card(Card::Rank::KING, Card::Suit::DIAMONDS), "KD"},
        {Card(Card::Rank::ACE, Card::Suit::HEARTS), "AH"},
        {Card(Card::Rank::TWO, Card::Suit::HEARTS), "2H"},
        {Card(Card::Rank::THREE, Card::Suit::HEARTS), "3H"},
        {Card(Card::Rank::FOUR, Card::Suit::HEARTS), "4H"},
        {Card(Card::Rank::FIVE, Card::Suit::HEARTS), "5H"},
        {Card(Card::Rank::SIX, Card::Suit::HEARTS), "6H"},
        {Card(Card::Rank::SEVEN, Card::Suit::HEARTS), "7H"},
        {Card(Card::Rank::EIGHT, Card::Suit::HEARTS), "8H"},
        {Card(Card::Rank::NINE, Card::Suit::HEARTS), "9H"},
        {Card(Card::Rank::TEN, Card::Suit::HEARTS), "10H"},
        {Card(Card::Rank::JACK, Card::Suit::HEARTS), "JH"},
        {Card(Card::Rank::QUEEN, Card::Suit::HEARTS), "QH"},
        {Card(Card::Rank::KING, Card::Suit::HEARTS), "KH"},
        {Card(Card::Rank::ACE, Card::Suit::SPADES), "AS"},
        {Card(Card::Rank::TWO, Card::Suit::SPADES), "2S"},
        {Card(Card::Rank::THREE, Card::Suit::SPADES), "3S"},
        {Card(Card::Rank::FOUR, Card::Suit::SPADES), "4S"},
        {Card(Card::Rank::FIVE, Card::Suit::SPADES), "5S"},
        {Card(Card::Rank::SIX, Card::Suit::SPADES), "6S"},
        {Card(Card::Rank::SEVEN, Card::Suit::SPADES), "7S"},
        {Card(Card::Rank::EIGHT, Card::Suit::SPADES), "8S"},
        {Card(Card::Rank::NINE, Card::Suit::SPADES), "9S"},
        {Card(Card::Rank::TEN, Card::Suit::SPADES), "10S"},
        {Card(Card::Rank::JACK, Card::Suit::SPADES), "JS"},
        {Card(Card::Rank::QUEEN, Card::Suit::SPADES), "QS"},
        {Card(Card::Rank::KING, Card::Suit::SPADES), "KS"}};

    countToPlayerLabel = {
        ui->card1Label, ui->card2Label, ui->card3Label, ui->card4Label, ui->card5Label, ui->card6Label, ui->card7Label, ui->card8Label, ui->card9Label, ui->card10Label
    };

    countToDealerLabel = {
        ui->card10Label_2, ui->card9Label_2, ui->card8Label_2, ui->card7Label_2, ui->card6Label_2, ui->card5Label_2, ui->card4Label_2, ui->card3Label_2, ui->card2Label_2, ui->card1Label_2
    };

    deck = std::make_unique<Deck>();
    player = std::make_unique<Player>();
    dealer = std::make_unique<Player>();

    deck->shuffledeck();

    connect(ui->twistButton, &QPushButton::clicked, this, [=]
            { playerTurn(); });
    connect(ui->stickButton, &QPushButton::clicked, this, [=]
            {
        // To prevent users from activating function before the function ending.
        this->setEnabled(false);
        ui->statusLabel->setText("Stick");
        ui->playagainButton->setEnabled(true);
        ui->twistButton->setEnabled(false);
        ui->stickButton->setEnabled(false);

        //Generating Computer score
        computerTurn();
    });

    connect(ui->playagainButton, &QPushButton::clicked, this, [=]{reset();});

    turnCount = 0;
    player_wins = 0;
    computer_wins = 0;
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
        ui->statusLabel->setText("Bust!");
        ui->twistButton->setEnabled(false);

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
    while (dealer->getHandValue() < 16){
        dealer->addCard(deck->drawCard());
        QPixmap img = QPixmap(":/images/cards/" + cardToImg[dealer->getLastCard()] + ".png");
        img = img.scaled(ui->card10Label->size().width(), ui->card10Label->size().height(), Qt::KeepAspectRatio);

        ui->computerScoreLabel->setText("Computer: " + QString::number(dealer->getHandValue()));

        countToDealerLabel[turnCount]->setPixmap(img);

        turnCount++;
    }

    //if computer is bust
    ui->computerStatusLabel->setText(dealer->getHandValue() > 21 ? "Bust!" : "Stick");

    // if same score or both bust
    if ((dealer->getHandValue() == player->getHandValue()) || ((dealer->getHandValue() > 21) && (player->getHandValue() > 21))){
        ui->outcomeLabel->setPixmap(draw);
    }
    // if both players are not bust AND computer is larger than player
    else if (
            ((dealer->getHandValue() < 22) && (player->getHandValue() < 22)
              && (dealer->getHandValue() > player->getHandValue()))
            || ((player->getHandValue() > 21) && dealer->getHandValue() < 22 )){
        ui->outcomeLabel->setPixmap(lose);;
        computer_wins++;
    }
    // else, player wins
    else{
        ui->outcomeLabel->setPixmap(win);
        player_wins++;
    }
    ui->statusbar->showMessage("Player " + QString::number(player_wins) + " - Gamescore - " + "Computer " + QString::number(computer_wins));
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
    ui->computerStatusLabel->setText("");
    ui->statusLabel->setText("");
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

playWindow::~playWindow()
{
    delete ui;
}
