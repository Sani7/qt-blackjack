#ifndef PLAYWINDOW_HPP
#define PLAYWINDOW_HPP

#include <QMainWindow>
#include <QtWidgets>
#include <QString>
#include <unordered_map>

#include "Deck.hpp"
#include "Player.hpp"

namespace Ui
{
    class playWindow;
}

    template <>
    struct std::hash<Card>
    {
        std::size_t operator()(const Card& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return ((hash<int>()((int)k.getRank())
                     ^ (hash<int>()((int)k.getSuit()) << 1)) >> 1);
        }
    };

class playWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit playWindow(QWidget *parent = nullptr);
    ~playWindow();
    void playerTurn(void);
    void computerTurn(void);
    void reset(void);
    int8_t calculate_winner(Player* player, Player* dealer);
private:
    Ui::playWindow *ui;

    std::unordered_map<Card, QString> cardToImg;
    QList<QLabel*> countToPlayerLabel;
    QList<QLabel*> countToDealerLabel;

    std::unique_ptr<Deck> deck;
    std::unique_ptr<Player> dealer;
    std::unique_ptr<Player> player;
    uint8_t turnCount;
    int player_wins;
    int computer_wins;
};

#endif // PLAYWINDOW_HPP
