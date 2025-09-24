#include "Background.h"
#include "Constants.h"
#include <cmath>

Background::Background() : m_bitmap(nullptr) {
}

Background::~Background() {
    if (m_bitmap) {
        DeleteObject(m_bitmap);
    }
}

bool Background::loadBitmap(const wchar_t* filename) {
    m_bitmap = (HBITMAP)LoadImage(nullptr, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    return m_bitmap != nullptr;
}

void Background::draw(HDC hdc, int width, int height) {
    // Fundo gradiente moderno - azul escuro para azul médio
    for (int y = 0; y < height; y++) {
        double ratio = (double)y / height;
        int r = (int)(20 + ratio * 15);
        int g = (int)(40 + ratio * 40);
        int b = (int)(80 + ratio * 60);

        HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
        RECT line = {0, y, width, y + 1};
        FillRect(hdc, &line, brush);
        DeleteObject(brush);
    }

    // Adicionar padrão sutil de onda
    drawWavePattern(hdc, width, height);
}

void Background::drawWavePattern(HDC hdc, int width, int height) {
    HPEN wavePen = CreatePen(PS_SOLID, 1, RGB(40, 80, 120));
    HGDIOBJ oldPen = SelectObject(hdc, wavePen);

    for (int y = 100; y < height - 100; y += 30) {
        for (int x = 0; x < width; x += 10) {
            double wave = sin(x * 0.02) * 3;
            SetPixel(hdc, x, y + (int)wave, RGB(60, 100, 160));
        }
    }

    SelectObject(hdc, oldPen);
    DeleteObject(wavePen);
}

void Background::drawWaterEffect(HDC hdc, RECT rect, double time) {
    // Efeito de água mais suave e realista
    int waterLevel = rect.bottom - 80;

    HBRUSH waterBrush = CreateSolidBrush(RGB(30, 80, 140));
    RECT waterRect = {rect.left, waterLevel, rect.right, rect.bottom};
    FillRect(hdc, &waterRect, waterBrush);
    DeleteObject(waterBrush);

    // Ondulações dinâmicas
    HPEN wavePen = CreatePen(PS_SOLID, 2, RGB(60, 120, 200));
    HGDIOBJ oldPen = SelectObject(hdc, wavePen);

    for (int i = 0; i < 3; i++) {
        int waveY = waterLevel + i * 15;
        MoveToEx(hdc, rect.left, waveY, nullptr);

        for (int x = rect.left; x < rect.right; x += 5) {
            double wave = sin(x * 0.05 + time * 2 + i) * (8 - i * 2);
            LineTo(hdc, x, waveY + (int)wave);
        }
    }

    SelectObject(hdc, oldPen);
    DeleteObject(wavePen);
}