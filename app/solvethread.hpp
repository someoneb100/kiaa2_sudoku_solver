#pragma once

#include "board.hpp"

#include <QThread>
#include <QSharedData>

struct Result : QSharedData {
    Result(const std::vector<Board>& b) : m_boards(b) {}
    Result(std::vector<Board>&& b) : m_boards(std::move(b)) {}
    Result(const Result&) = default;
    std::vector<Board> m_boards;
};

class SolveThread : public QThread {
    Q_OBJECT
public:
    SolveThread(const Board&, QObject* parent = nullptr);

    Board m_board;

signals:
    void solution(QSharedDataPointer<Result>);

protected:
    void run() override;
};
