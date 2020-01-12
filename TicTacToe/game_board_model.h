#ifndef FIELD_H
#define FIELD_H

#include <QAbstractListModel>
#include <QStringList>

class Field
{
public:
    Field(const int mark = 0, const bool highlight_field = false);

    int mark() const;
    bool highlightField() const;

    void setMark(int value);
    void setHighlightField(bool value);

private:
    int m_mark;
    bool m_highlight;
};

class Marks
{
    Q_GADGET
public:
    enum Mark {
        Empty,
        Nought,
        Cross
    };
    Q_ENUM(Mark)
private:
    explicit Marks();
};


class GameBoardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum FieldRoles {
        MarkRole = Qt::UserRole + 1,
        HighlightFieldRole
    };

    GameBoardModel(QObject *parent = 0);
    void createBoard(unsigned int width, unsigned int height);
    void addField(const Field &field);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool player_wins(QModelIndex& index, int marks_required, int player_symbol);
    bool count_marks(int x, int y, int player_symbol);
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Field> m_fields;
    unsigned int m_board_width;
    unsigned int m_board_height;

    bool highlight_field(int x, int y, int player_symbol);
};

#endif // FIELD_H
