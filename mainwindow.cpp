#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cols(8)
    , rows(7)
    , currentPlayer(1)
    , highlightedColumn(-1) // Inicialmente ninguna columna está resaltada
{
    ui->setupUi(this);
    tablero.resize(rows, QVector<int>(cols, 0)); // Inicializo tablero de juego a 0
    setMinimumSize(cols * 40, rows * 40);

    // Activar seguimiento del ratón
    setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect geom = ui->centralwidget->geometry();
    int width = geom.width();
    int height = geom.height();

    if ((width / cols) < (height / rows))
    {
        cellSize = width / cols;
    }
    else
    {
        cellSize = height / rows;
    }

    int x0 = (width - (cols * cellSize)) / 2;
    int y0 = (height - (rows * cellSize)) / 2;

    // Dibujar fondo
    painter.setBrush(Qt::lightGray);
    painter.drawRect(x0, y0, cols * cellSize, rows * cellSize);

    // Dibujar celdas del tablero
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            QRect circleRect(x0 + (c * cellSize + 5), y0 + (r * cellSize + 5), cellSize - 10, cellSize - 10);

            if (tablero[r][c] == 0)
            {
                painter.setBrush(Qt::white);
            }
            else if (tablero[r][c] == 1)
            {
                painter.setBrush(Qt::red);
            }
            else
            {
                painter.setBrush(Qt::yellow);
            }

            painter.drawEllipse(circleRect);
        }
    }

    // Dibujar círculo para la ficha "fantasma" en la columna resaltada
    if (highlightedColumn != -1)
    {
        // Buscar la fila más baja disponible en la columna resaltada
        int dropRow = -1;
        for (int r = rows - 1; r >= 0; r--)
        {
            if (tablero[r][highlightedColumn] == 0)
            {
                dropRow = r;
                break;
            }
        }

        if (dropRow != -1)
        {
            // Dibujar el círculo "fantasma" donde iría la ficha
            QRect ghostCircleRect(
                x0 + (highlightedColumn * cellSize + 5),
                y0 + (dropRow * cellSize + 5),
                cellSize - 10,
                cellSize - 10);

            painter.setBrush(QColor(200, 200, 255, 128)); // Color semitransparente
            painter.drawEllipse(ghostCircleRect);
        }
    }
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)                   // Si se pulsa click izquierdo
    {
        int x = event->pos().x();

        QRect geom = ui->centralwidget->geometry();
        int width = geom.width();
        int x0 = (width - (cols * cellSize)) / 2;
        // hay que restar el x0
        int column = (x - x0) / cellSize;
        if(column >= 0 && column < cols)
        {
            int row;
            if(dropDisc(column, row))
            {
                update();

                // Verificar si el movimiento actual gana el juego
                if(checkWin(row, column))
                {
                    QMessageBox::information(this, "Victoria", QString("¡Jugador %1 ha ganado!").arg(currentPlayer));
                    return;
                }

                // Cambiar de jugador
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
            else
            {
                QMessageBox::warning(this, "Columna Llena", "La columna seleccionada está llena. Por favor, elige otra");
            }
        }
    }
}

bool MainWindow::dropDisc(int column, int &row)
{
    // Recorrer las filas desde la parte inferior hacia arriba
    for(row = rows - 1; row >= 0; row--)
    {
        if(tablero[row][column] == 0) // Si la celda está vacía
        {
            tablero[row][column] = currentPlayer; // Colocar la ficha del jugador actual
            return true; // Ficha colocada con éxito
        }
    }

    // Si llegamos aquí, la columna está llena
    return false;
}

// Reutilizable para simular partida contra la CPU
bool MainWindow::checkWin(int row, int col)
{
    int player = tablero[row][col];
    if(player == 0)
        return false;

    // Direcciones: horizontal, vertical, diagonal /, diagonal \*
    const QVector<QPair<int, int>> directions = { {0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for(auto &dir : directions)
    {
        int count = 1;

        // Dirección positiva
        int r = row + dir.first;
        int c = col + dir.second;
        while(r >= 0 && r < rows && c >= 0 && c < cols && tablero[r][c] == player)
        {
            count++;
            r += dir.first;
            c += dir.second;
        }

        // Dirección negativa
        r = row - dir.first;
        c = col - dir.second;
        while(r >= 0 && r < rows && c >= 0 && c < cols && tablero[r][c] == player)
        {
            count++;
            r -= dir.first;
            c -= dir.second;
        }

        if(count >= 4)
            return true;
    }
    return false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Actualizar la columna resaltada según la posición del ratón
    int mouseX = event->pos().x();
    updateHighlightedColumn(mouseX);
}

void MainWindow::updateHighlightedColumn(int mouseX)
{
    QRect geom = ui->centralwidget->geometry();
    int width = geom.width();
    int x0 = (width - (cols * cellSize)) / 2;

    int column = (mouseX - x0) / cellSize;
    if (column >= 0 && column < cols && column != highlightedColumn)
    {
        highlightedColumn = column;
        update(); // Forzar redibujado
    }
    else if (column < 0 || column >= cols) // Si el ratón está fuera del área
    {
        if (highlightedColumn != -1)
        {
            highlightedColumn = -1; // Quitar el resaltado
            update();
        }
    }
}
