#include "game_board_model.h"
#include <QtDebug>

Field::Field(const int mark, const bool highlight_field)
    : m_mark(mark), m_highlight(highlight_field)
{
}

int Field::mark() const
{
    return m_mark;
}

bool Field::highlightField() const
{
    return m_highlight;
}

void Field::setMark(int value)
{
    m_mark = value;
}

void Field::setHighlightField(bool value)
{
    m_highlight = value;
}

GameBoardModel::GameBoardModel(QObject *parent)
    : QAbstractListModel(parent),
    m_board_width(0), m_board_height(0)
{
}

void GameBoardModel::createBoard(unsigned int width, unsigned int height)
{
    int size = width*height;
    m_board_width = width;
    m_board_height = height;
    m_fields.clear();
    for(int i = 0; i<size; i++)
    {
        addField(Field());
    }
}

void GameBoardModel::addField(const Field &field)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_fields << field;
    endInsertRows();
}

int GameBoardModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_fields.count();
}

QVariant GameBoardModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_fields.count())
        return QVariant();

    const Field &field = m_fields[index.row()];
    if (role == MarkRole)
        return field.mark();
    else if (role == HighlightFieldRole)
        return field.highlightField();
    return QVariant();
}

bool GameBoardModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
    {
        return false;
    }
    Field &item = m_fields[index.row()];
    if (role == MarkRole) item.setMark(value.toInt());
    else if (role == HighlightFieldRole) item.setHighlightField(value.toBool());
    else return false;

    emit dataChanged(index, index, { role } );

    return true;
}

QHash<int, QByteArray> GameBoardModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[MarkRole] = "mark";
    roles[HighlightFieldRole] = "highlightField";
    return roles;
}

bool GameBoardModel::player_wins(QModelIndex &index, int marks_required, int player_symbol)
{
    int x = index.row() % m_board_width;
    int y = index.row() / m_board_width;

    int i = 1, j = 1;
    int total_in_direction = 1;

    while(count_marks(x-i, y, player_symbol)) { total_in_direction++; i++; }
    while(count_marks(x+j, y, player_symbol)) { total_in_direction++; j++; }

    if(total_in_direction >= marks_required) {
        i = 0; j = 0;
        while(highlight_field(x-i, y, player_symbol)) { i++; }
        while(highlight_field(x+j, y, player_symbol)) { j++; }
        return true;
    }

    i = 1; j = 1; total_in_direction = 1;
    while(count_marks(x, y-i, player_symbol)) { total_in_direction++; i++; }
    while(count_marks(x, y+j, player_symbol)) { total_in_direction++; j++; }

    if(total_in_direction >= marks_required)
    {
        i = 0; j = 0;
        while(highlight_field(x, y-i, player_symbol)) { i++; }
        while(highlight_field(x, y+j, player_symbol)) { j++; }
        return true;
    }

    i = 1; j = 1; total_in_direction = 1;
    while(count_marks(x-i, y-i, player_symbol)) { total_in_direction++; i++; }
    while(count_marks(x+j, y+j, player_symbol)) { total_in_direction++; j++; }

    if(total_in_direction >= marks_required)
    {
        i = 0; j = 0;
        while(highlight_field(x-i, y-i, player_symbol)) { i++; }
        while(highlight_field(x+j, y+j, player_symbol)) { j++; }
        return true;
    }

    i = 1; j = 1; total_in_direction = 1;
    while(count_marks(x+i, y-i, player_symbol)) { total_in_direction++; i++; }
    while(count_marks(x-j, y+j, player_symbol)) { total_in_direction++; j++; }

    if(total_in_direction >= marks_required)
    {
        i = 0; j = 0;
        while(highlight_field(x+i, y-i, player_symbol)) { i++; }
        while(highlight_field(x-j, y+j, player_symbol)) { j++; }
        return true;
    }

    return false;
}

bool GameBoardModel::count_marks(int x, int y, int player_symbol)
{
    int index = m_board_width*y+x;
    //qDebug() << "Index: " << index << ", x:" << x << ", y:" << y;

    if(x<0 || y<0 || x>=(int)m_board_width || y>=(int)m_board_width) return false;

    if(index >= m_fields.size()) return false;
    return m_fields.at(index).mark() == player_symbol;
}

bool GameBoardModel::highlight_field(int x, int y, int player_symbol)
{
    int index = m_board_width*y+x;
    qDebug() << "highlight: Index: " << index << ", x:" << x << ", y:" << y;
    if(x<0 || y<0 || x>=(int)m_board_width || y>=(int)m_board_width) return false;

    if(index >= m_fields.size()) return false;

    if(m_fields.at(index).mark() == player_symbol){
        setData(GameBoardModel::index(index), true, GameBoardModel::HighlightFieldRole);
        return true;
    }
    return false;
}
