#pragma once

namespace ImageRedactor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
    private:
        System::Windows::Forms::ToolStrip^ toolStrip2;

        System::Windows::Forms::ToolStripMenuItem^ increaseZoomToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ decreaseZoomToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ resetZoomToolStripMenuItem;

        System::Windows::Forms::ToolStripMenuItem^ cutToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ copyToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ pasteToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ deleteToolStripMenuItem;

        System::Windows::Forms::ToolStripSeparator^ toolStripSeparator4;
        System::Windows::Forms::ToolStripMenuItem^ closeToolStripMenuItem;

        System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;
        System::Windows::Forms::ToolStripMenuItem^ saveAsToolStripMenuItem;

        System::Windows::Forms::ToolStripMenuItem^ createNewToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ openExistingToolStripMenuItem;

        System::Windows::Forms::PictureBox^ pictureBox1;

        System::Windows::Forms::TabControl^ tabControl1;
        System::Windows::Forms::TabPage^ tabPage1;
        System::Windows::Forms::MenuStrip^ menuStrip1;
        System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ editToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ viewToolStripMenuItem;
        System::Windows::Forms::Panel^ panel1;
        System::Windows::Forms::ToolStrip^ toolStrip1;
        System::Windows::Forms::ToolStripButton^ drawBrushSelectionTool;
        System::Windows::Forms::ToolStripButton^ pickBrushSelectionTool;
        System::Windows::Forms::ToolStripButton^ fillBrushSelectionTool;
        System::Windows::Forms::ToolStripButton^ selectBrushSelectionTool;
        System::Windows::Forms::ToolStripButton^ blendBrushSelectionTool;
        System::Windows::Forms::ToolStripButton^ clearBrushSelectionTool;
        System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
        System::Windows::Forms::ToolStripButton^ toolStripButton9;
        System::Windows::Forms::ToolStripButton^ toolStripButton8;
        System::Windows::Forms::Panel^ panel2;
        System::Windows::Forms::ColorDialog^ colorDialog1;
        System::Windows::Forms::ToolStripLabel^ toolNameLabel;
        System::Windows::Forms::ToolStripButton^ squareBrushSelector;
        System::Windows::Forms::ToolStripButton^ circleBrushSelector;
        System::Windows::Forms::ToolStripButton^ smoothBrushSelector;
        System::Windows::Forms::ToolStripComboBox^ widthSelectorBox;
        System::Windows::Forms::ToolStripSeparator^ toolStripSeparator6;
        System::Windows::Forms::ToolStripSeparator^ toolStripSeparator5;
        System::Windows::Forms::ToolStripMenuItem^ clearPictureToolStripMenuItem;
        System::Windows::Forms::ToolStripSeparator^ toolStripSeparator7;
        System::Windows::Forms::ToolStripLabel^ toolStripLabel2;
        System::Windows::Forms::ToolStripSeparator^ toolStripSeparator8;
        System::Windows::Forms::ToolStripLabel^ toolStripLabel3;
        System::Windows::Forms::ToolStripComboBox^ accessSelectorBox;
        System::Windows::Forms::ToolStripSeparator^ toolStripSeparator9;
        System::Windows::Forms::ToolStripLabel^ toolStripLabel4;
        System::Windows::Forms::ToolStripComboBox^ factorSelectorBox;
        System::Windows::Forms::OpenFileDialog^ openFileDialog1;
        System::Windows::Forms::SaveFileDialog^ saveFileDialog1;


    public:
        enum class SelectedBrush
        {
            None, Clear, Draw, Blend, FloodFill, Select, PickColor
        };

        enum class ActiveBrush
        {
            None, Pasting, Selecting, ColorPicker, Drawing
        };

        enum class SelectedBrushType
        {
            Circular, Rectangular
        };

        enum class SelectedSmoothType
        {
            Smooth, Sharp
        };

    private:
        System::Drawing::Color _foreColor = System::Drawing::Color::Black;
        System::Drawing::Color _backColor = System::Drawing::Color::Black;

        System::Drawing::Bitmap^ canvasBitmap;
        System::Drawing::Graphics^ canvasGraphics;

    public:
        System::Drawing::SolidBrush^ ForeColorBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
        System::Drawing::SolidBrush^ BackColorBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::White);
        System::Drawing::Pen^ ForeColorPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
        System::Drawing::Pen^ BackColorPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);

    private:
        int optID;

        SelectedBrush selectedBrush = SelectedBrush::None;
        ActiveBrush activeBrush = ActiveBrush::None;
        SelectedBrushType selectedBrushType = SelectedBrushType::Circular;
        SelectedSmoothType selectedSmoothType = SelectedSmoothType::Smooth;

        float zoomFactor = 1.0f;

        bool isPanning = false;
        System::Drawing::Point panMouseStart;
        System::Drawing::Point panScrollStart;

        System::Drawing::Point selectionStartPoint = System::Drawing::Point::Empty;
        System::Drawing::Rectangle selectionRect = System::Drawing::Rectangle::Empty;
        System::Drawing::Rectangle rendSelectionRect = System::Drawing::Rectangle::Empty;

        System::Drawing::Bitmap^ pastedPreview = nullptr;
        System::Drawing::Point pastedPreviewLocation = System::Drawing::Point::Empty;
        float access = 0.1f;
        float factor = 0.1f;

        System::Drawing::Point prevDrawPoint = System::Drawing::Point::Empty;
        int brushRadius = 10;

        int eyedropperZoom = 8;
        int eyedropperRadius = 8;
        System::Drawing::Point eyedropperPosition = System::Drawing::Point::Empty;

    public:
        property System::Drawing::Color SelectedForeColor
        {
            System::Drawing::Color get()
            {
                return _foreColor;
            }
            void set(System::Drawing::Color value)
            {
                _foreColor = value;
                ForeColorBrush = gcnew System::Drawing::SolidBrush(value);
                ForeColorPen = gcnew System::Drawing::Pen(value);
            }
        }

        property System::Drawing::Color SelectedBackColor
        {
            System::Drawing::Color get()
            {
                return _backColor;
            }
            void set(System::Drawing::Color value)
            {
                _backColor = value;
                BackColorBrush = gcnew System::Drawing::SolidBrush(value);
                BackColorPen = gcnew System::Drawing::Pen(value);
            }
        }

    private:
        System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            if (e->Button == System::Windows::Forms::MouseButtons::Middle)
            {
                isPanning = true;
                panMouseStart = panel2->PointToClient(System::Windows::Forms::Control::MousePosition);
                panScrollStart = System::Drawing::Point(-panel2->AutoScrollPosition.X, -panel2->AutoScrollPosition.Y);
                pictureBox1->Cursor = System::Windows::Forms::Cursors::Hand;
            }

            if (e->Button == System::Windows::Forms::MouseButtons::Left && activeBrush == ActiveBrush::Pasting)
            {
                System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(canvasBitmap);
                try
                {
                    System::Drawing::Rectangle renderRect = System::Drawing::Rectangle(
                        (int)(pastedPreviewLocation.X / zoomFactor),
                        (int)(pastedPreviewLocation.Y / zoomFactor),
                        pastedPreview->Width,
                        pastedPreview->Height
                    );
                    g->DrawImage(pastedPreview, renderRect);
                }
                finally
                {
                    delete g;
                    delete pastedPreview;
                }
                activeBrush = ActiveBrush::Pasting;
                pastedPreview = nullptr;
                pictureBox1->Invalidate();
            }

            System::Drawing::Point p;

            if (e->Button == System::Windows::Forms::MouseButtons::Left)
            {
                switch (selectedBrush)
                {
                case SelectedBrush::Clear:
                    activeBrush = ActiveBrush::Drawing;
                    prevDrawPoint = GetAt(e->Location);
                    DrawAtPoint(prevDrawPoint, SelectedBackColor);
                    break;
                case SelectedBrush::Draw:
                    activeBrush = ActiveBrush::Drawing;
                    prevDrawPoint = GetAt(e->Location);
                    DrawAtPoint(prevDrawPoint, SelectedForeColor);
                    break;
                case SelectedBrush::Select:
                    activeBrush = ActiveBrush::Selecting;
                    selectionStartPoint = GetAt(e->Location);
                    selectionRect = System::Drawing::Rectangle(GetAt(e->Location), System::Drawing::Size::Empty);
                    rendSelectionRect = System::Drawing::Rectangle(e->Location, System::Drawing::Size::Empty);
                    pictureBox1->Invalidate();
                    break;
                case SelectedBrush::FloodFill:
                    if (selectedSmoothType == SelectedSmoothType::Smooth)
                        FloodFillSoft(canvasBitmap, GetAt(e->Location), SelectedForeColor, (int)(access * 100), factor);
                    else
                        FloodFill(canvasBitmap, GetAt(e->Location), SelectedForeColor, (int)(access * 100));
                    activeBrush = ActiveBrush::Drawing;
                    pictureBox1->Refresh();
                    break;
                case SelectedBrush::PickColor:
                    if (activeBrush == ActiveBrush::None)
                    {
                        System::Console::WriteLine("DONE!!!");
                        activeBrush = ActiveBrush::ColorPicker;
                    }

                    p = GetAt(e->Location);
                    if (p.X >= 0 && p.X < canvasBitmap->Width && p.Y >= 0 && p.Y < canvasBitmap->Height)
                    {
                        System::Drawing::Color picked = canvasBitmap->GetPixel(p.X, p.Y);
                        colorDialog1->Color = picked;
                        SelectedForeColor = picked;
                        toolStripButton8->BackColor = picked;
                        pictureBox1->Invalidate();
                    }
                    pictureBox1->Invalidate();
                    return;
                    break;
                default:
                    activeBrush = ActiveBrush::Drawing;
                    break;
                }
            }

            if (e->Button == System::Windows::Forms::MouseButtons::Right && activeBrush == ActiveBrush::Pasting)
            {
                activeBrush = ActiveBrush::None;
                delete pastedPreview;
                pastedPreview = nullptr;
                pictureBox1->Invalidate();
            }

            if (e->Button == System::Windows::Forms::MouseButtons::Right && (selectedBrush == SelectedBrush::PickColor))
            {
                activeBrush = ActiveBrush::None;
                pictureBox1->Refresh();
            }
        }

    private:
        System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            if (e->Button == System::Windows::Forms::MouseButtons::Left)
                activeBrush = ActiveBrush::None;

            if (e->Button == System::Windows::Forms::MouseButtons::Middle)
            {
                isPanning = false;
                pictureBox1->Cursor = System::Windows::Forms::Cursors::Default;
            }

            if (e->Button == System::Windows::Forms::MouseButtons::Left && activeBrush == ActiveBrush::Selecting)
            {
                activeBrush = ActiveBrush::None;
                pictureBox1->Invalidate();
            }
        }

    public:
        System::Drawing::Point GetAt(System::Drawing::Point p)
        {
            int x = (int)(p.X / zoomFactor);
            int y = (int)(p.Y / zoomFactor);
            return System::Drawing::Point(x, y);
        }

    private:
        System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            if (isPanning)
            {
                System::Drawing::Point mouseNow = panel2->PointToClient(System::Windows::Forms::Control::MousePosition);

                int dx = mouseNow.X - panMouseStart.X;
                int dy = mouseNow.Y - panMouseStart.Y;

                System::Drawing::Point newScroll = System::Drawing::Point(panScrollStart.X + dx * 2, panScrollStart.Y + dy * 2);
                panel2->AutoScrollPosition = newScroll;
            }

            switch (activeBrush)
            {
            case ActiveBrush::Pasting:
            {
                System::Drawing::Point imgPt = e->Location;
                pastedPreviewLocation = imgPt;
                pictureBox1->Invalidate();
                break;
            }
            case ActiveBrush::Selecting:
            {
                System::Drawing::Point mouseNow = GetAt(e->Location);

                int x1 = selectionStartPoint.X;
                int y1 = selectionStartPoint.Y;
                int x2 = mouseNow.X;
                int y2 = mouseNow.Y;

                int rectX = Math::Min(x1, x2);
                int rectY = Math::Min(y1, y2);
                int rectWidth = Math::Abs(x2 - x1);
                int rectHeight = Math::Abs(y2 - y1);

                selectionRect = System::Drawing::Rectangle(rectX, rectY, rectWidth, rectHeight);

                rendSelectionRect = System::Drawing::Rectangle(
                    (int)(rectX * zoomFactor),
                    (int)(rectY * zoomFactor),
                    (int)(rectWidth * zoomFactor),
                    (int)(rectHeight * zoomFactor)
                );
                pictureBox1->Invalidate();
                break;
            }
            case ActiveBrush::ColorPicker:
            {
                eyedropperPosition = GetAt(e->Location);
                pictureBox1->Invalidate();
                break;
            }
            case ActiveBrush::Drawing:
            {
                System::Drawing::Point pres = GetAt(e->Location);
                switch (selectedBrush)
                {
                case SelectedBrush::Draw:
                {
                    System::Drawing::Point current1 = GetAt(e->Location);
                    DrawLineBetween(prevDrawPoint, current1, SelectedForeColor);
                    prevDrawPoint = current1;
                    break;
                }
                case SelectedBrush::Clear:
                {
                    System::Drawing::Point current2 = GetAt(e->Location);
                    DrawLineBetween(prevDrawPoint, current2, SelectedBackColor);
                    prevDrawPoint = current2;
                    break;
                }
                case SelectedBrush::Blend:
                {
                    if (selectedBrushType == SelectedBrushType::Rectangular)
                        BlendToolRect(canvasBitmap, pres, brushRadius * 2, brushRadius * 2, factor);
                    else
                        BlendToolCircle(canvasBitmap, pres, brushRadius, factor);
                    break;
                }
                }
                pictureBox1->Invalidate();
                break;
            }
            }
        }

    private:
        System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e)
        {
        }

    private:
        System::Void toolStripButton8_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                SelectedForeColor = colorDialog1->Color;
                toolStripButton8->BackColor = SelectedForeColor;
            }
        }

    private:
        System::Void toolStripButton8_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
        }

    private:
        System::Void toolStripButton9_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                SelectedBackColor = colorDialog1->Color;
                toolStripButton9->BackColor = SelectedBackColor;
            }
        }

        void BlendToolCircle(System::Drawing::Bitmap^ bmp, System::Drawing::Point center, int radius, float blendFactor)
        {
            if (blendFactor <= 0.0f || radius <= 0) return;

            System::Drawing::Rectangle rect(
                Math::Max(0, center.X - radius),
                Math::Max(0, center.Y - radius),
                Math::Min(bmp->Width - center.X + radius, radius * 2),
                Math::Min(bmp->Height - center.Y + radius, radius * 2)
            );

            System::Drawing::Imaging::BitmapData^ data = bmp->LockBits(
                System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height),
                System::Drawing::Imaging::ImageLockMode::ReadWrite,
                System::Drawing::Imaging::PixelFormat::Format32bppArgb
            );

            int stride = data->Stride;
            int bytesPerPixel = 4;
            int width = bmp->Width;
            int height = bmp->Height;
            System::IntPtr ptr = data->Scan0;
            int byteCount = stride * height;
            array<System::Byte>^ pixels = gcnew array<System::Byte>(byteCount);
            System::Runtime::InteropServices::Marshal::Copy(ptr, pixels, 0, byteCount);

            int rSum = 0, gSum = 0, bSum = 0, count = 0;

            for (int y = rect.Top; y < rect.Bottom; y++)
            {
                for (int x = rect.Left; x < rect.Right; x++)
                {
                    double dx = x - center.X;
                    double dy = y - center.Y;
                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        int i = y * stride + x * bytesPerPixel;
                        bSum += pixels[i];
                        gSum += pixels[i + 1];
                        rSum += pixels[i + 2];
                        count++;
                    }
                }
            }

            if (count == 0)
            {
                bmp->UnlockBits(data);
                return;
            }

            System::Byte rAvg = (System::Byte)(rSum / count);
            System::Byte gAvg = (System::Byte)(gSum / count);
            System::Byte bAvg = (System::Byte)(bSum / count);

            for (int y = rect.Top; y < rect.Bottom; y++)
            {
                for (int x = rect.Left; x < rect.Right; x++)
                {
                    double dx = x - center.X;
                    double dy = y - center.Y;
                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        int i = y * stride + x * bytesPerPixel;

                        pixels[i] = (System::Byte)(pixels[i] * (1 - blendFactor) + bAvg * blendFactor);
                        pixels[i + 1] = (System::Byte)(pixels[i + 1] * (1 - blendFactor) + gAvg * blendFactor);
                        pixels[i + 2] = (System::Byte)(pixels[i + 2] * (1 - blendFactor) + rAvg * blendFactor);
                    }
                }
            }

            System::Runtime::InteropServices::Marshal::Copy(pixels, 0, ptr, byteCount);
            bmp->UnlockBits(data);
        }

        void BlendToolRect(System::Drawing::Bitmap^ bmp, System::Drawing::Point center, int width, int height, float blendFactor)
        {
            if (blendFactor <= 0.0f || width <= 0 || height <= 0) return;

            int halfW = width / 2;
            int halfH = height / 2;

            System::Drawing::Rectangle rect(
                Math::Max(0, center.X - halfW),
                Math::Max(0, center.Y - halfH),
                Math::Min(bmp->Width - center.X + halfW, width),
                Math::Min(bmp->Height - center.Y + halfH, height)
            );

            System::Drawing::Imaging::BitmapData^ data = bmp->LockBits(
                System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height),
                System::Drawing::Imaging::ImageLockMode::ReadWrite,
                System::Drawing::Imaging::PixelFormat::Format32bppArgb
            );

            int stride = data->Stride;
            int bytesPerPixel = 4;
            int widthBmp = bmp->Width;
            int heightBmp = bmp->Height;
            System::IntPtr ptr = data->Scan0;
            int byteCount = stride * heightBmp;
            array<System::Byte>^ pixels = gcnew array<System::Byte>(byteCount);
            System::Runtime::InteropServices::Marshal::Copy(ptr, pixels, 0, byteCount);

            int rSum = 0, gSum = 0, bSum = 0, count = 0;

            for (int y = rect.Top; y < rect.Bottom; y++)
            {
                for (int x = rect.Left; x < rect.Right; x++)
                {
                    int i = y * stride + x * bytesPerPixel;
                    bSum += pixels[i];
                    gSum += pixels[i + 1];
                    rSum += pixels[i + 2];
                    count++;
                }
            }

            if (count == 0)
            {
                bmp->UnlockBits(data);
                return;
            }

            System::Byte rAvg = (System::Byte)(rSum / count);
            System::Byte gAvg = (System::Byte)(gSum / count);
            System::Byte bAvg = (System::Byte)(bSum / count);

            for (int y = rect.Top; y < rect.Bottom; y++)
            {
                for (int x = rect.Left; x < rect.Right; x++)
                {
                    int i = y * stride + x * bytesPerPixel;

                    pixels[i] = (System::Byte)(pixels[i] * (1 - blendFactor) + bAvg * blendFactor);
                    pixels[i + 1] = (System::Byte)(pixels[i + 1] * (1 - blendFactor) + gAvg * blendFactor);
                    pixels[i + 2] = (System::Byte)(pixels[i + 2] * (1 - blendFactor) + rAvg * blendFactor);
                }
            }

            System::Runtime::InteropServices::Marshal::Copy(pixels, 0, ptr, byteCount);
            bmp->UnlockBits(data);
        }

        void FloodFill(System::Drawing::Bitmap^ bmp, System::Drawing::Point start, System::Drawing::Color targetColor, int tolerance)
        {
            if (tolerance < 0) tolerance = 0;
            if (tolerance > 255) tolerance = 255;

            System::Drawing::Imaging::BitmapData^ data = bmp->LockBits(
                System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height),
                System::Drawing::Imaging::ImageLockMode::ReadWrite,
                System::Drawing::Imaging::PixelFormat::Format32bppArgb
            );

            int stride = data->Stride;
            int width = bmp->Width;
            int height = bmp->Height;
            System::IntPtr ptr = data->Scan0;
            int bytesPerPixel = 4;
            array<System::Byte>^ pixels = gcnew array<System::Byte>(stride * height);
            System::Runtime::InteropServices::Marshal::Copy(ptr, pixels, 0, pixels->Length);

            int startX = start.X;
            int startY = start.Y;

            if (startX < 0 || startX >= width || startY < 0 || startY >= height)
            {
                bmp->UnlockBits(data);
                return;
            }

            int startIndex = startY * stride + startX * bytesPerPixel;
            System::Byte r0 = pixels[startIndex + 2];
            System::Byte g0 = pixels[startIndex + 1];
            System::Byte b0 = pixels[startIndex];

            array<bool, 2>^ visited = gcnew array<bool, 2>(width, height);
            System::Collections::Generic::Queue<System::Drawing::Point>^ queue = gcnew System::Collections::Generic::Queue<System::Drawing::Point>();
            queue->Enqueue(start);

            while (queue->Count > 0)
            {
                System::Drawing::Point pt = queue->Dequeue();
                int x = pt.X;
                int y = pt.Y;

                if (x < 0 || x >= width || y < 0 || y >= height) continue;
                if (visited[x, y]) continue;

                int i = y * stride + x * bytesPerPixel;
                System::Byte b = pixels[i];
                System::Byte g = pixels[i + 1];
                System::Byte r = pixels[i + 2];

                int diff = Math::Abs(r - r0) + Math::Abs(g - g0) + Math::Abs(b - b0);
                if (diff <= tolerance * 3)
                {
                    pixels[i] = targetColor.B;
                    pixels[i + 1] = targetColor.G;
                    pixels[i + 2] = targetColor.R;
                    visited[x, y] = true;

                    queue->Enqueue(System::Drawing::Point(x + 1, y));
                    queue->Enqueue(System::Drawing::Point(x - 1, y));
                    queue->Enqueue(System::Drawing::Point(x, y + 1));
                    queue->Enqueue(System::Drawing::Point(x, y - 1));
                }
            }

            System::Runtime::InteropServices::Marshal::Copy(pixels, 0, ptr, pixels->Length);
            bmp->UnlockBits(data);
        }

        void FloodFillSoft(System::Drawing::Bitmap^ bmp, System::Drawing::Point start, System::Drawing::Color targetColor, int tolerance, float softness)
        {
            if (tolerance < 0) tolerance = 0;
            if (tolerance > 255) tolerance = 255;
            if (softness < 0.0f) softness = 0.0f;
            if (softness > 1.0f) softness = 1.0f;

            System::Drawing::Imaging::BitmapData^ data = bmp->LockBits(
                System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height),
                System::Drawing::Imaging::ImageLockMode::ReadWrite,
                System::Drawing::Imaging::PixelFormat::Format32bppArgb
            );

            int stride = data->Stride;
            int width = bmp->Width;
            int height = bmp->Height;
            System::IntPtr ptr = data->Scan0;
            int bytesPerPixel = 4;
            array<System::Byte>^ pixels = gcnew array<System::Byte>(stride * height);
            System::Runtime::InteropServices::Marshal::Copy(ptr, pixels, 0, pixels->Length);

            int startX = start.X;
            int startY = start.Y;

            if (startX < 0 || startX >= width || startY < 0 || startY >= height)
            {
                bmp->UnlockBits(data);
                return;
            }

            int startIndex = startY * stride + startX * bytesPerPixel;
            System::Byte r0 = pixels[startIndex + 2];
            System::Byte g0 = pixels[startIndex + 1];
            System::Byte b0 = pixels[startIndex];

            array<bool, 2>^ visited = gcnew array<bool, 2>(width, height);
            System::Collections::Generic::Queue<System::Drawing::Point>^ queue = gcnew System::Collections::Generic::Queue<System::Drawing::Point>();
            queue->Enqueue(start);

            while (queue->Count > 0)
            {
                System::Drawing::Point pt = queue->Dequeue();
                int x = pt.X;
                int y = pt.Y;

                if (x < 0 || x >= width || y < 0 || y >= height) continue;
                if (visited[x, y]) continue;

                int i = y * stride + x * bytesPerPixel;
                System::Byte b = pixels[i];
                System::Byte g = pixels[i + 1];
                System::Byte r = pixels[i + 2];

                int diff = Math::Abs(r - r0) + Math::Abs(g - g0) + Math::Abs(b - b0);
                if (diff <= tolerance * 3)
                {
                    float alpha = 1.0f - (diff / (float)(tolerance * 3));
                    alpha = alpha * (1.0f - softness) + softness;

                    pixels[i] = (System::Byte)(pixels[i] * (1 - alpha) + targetColor.B * alpha);
                    pixels[i + 1] = (System::Byte)(pixels[i + 1] * (1 - alpha) + targetColor.G * alpha);
                    pixels[i + 2] = (System::Byte)(pixels[i + 2] * (1 - alpha) + targetColor.R * alpha);

                    visited[x, y] = true;

                    queue->Enqueue(System::Drawing::Point(x + 1, y));
                    queue->Enqueue(System::Drawing::Point(x - 1, y));
                    queue->Enqueue(System::Drawing::Point(x, y + 1));
                    queue->Enqueue(System::Drawing::Point(x, y - 1));
                }
            }

            System::Runtime::InteropServices::Marshal::Copy(pixels, 0, ptr, pixels->Length);
            bmp->UnlockBits(data);
        }

    private:
        void PerformZoom(System::Windows::Forms::MouseEventArgs^ e)
        {
            float oldZoom = zoomFactor;

            float scale = (e->Delta > 0) ? 1.1f : 0.9f;

            if (scale * zoomFactor > 9.0f)
            {
                HandledMouseEventArgs^ he = safe_cast<HandledMouseEventArgs^>(e);
                he->Handled = true;
                return;
            }

            zoomFactor *= scale;

            float scaleChange = zoomFactor / oldZoom;

            panel2->AutoScrollPosition = System::Drawing::Point(
                static_cast<int>(panel2->HorizontalScroll->Value * scaleChange),
                static_cast<int>(panel2->VerticalScroll->Value * scaleChange)
            );

            pictureBox1->Size = System::Drawing::Size(
                static_cast<int>(canvasBitmap->Width * zoomFactor),
                static_cast<int>(canvasBitmap->Height * zoomFactor)
            );

            rendSelectionRect = System::Drawing::Rectangle(
                static_cast<int>(selectionRect.X * zoomFactor),
                static_cast<int>(selectionRect.Y * zoomFactor),
                static_cast<int>(selectionRect.Width * zoomFactor),
                static_cast<int>(selectionRect.Height * zoomFactor)
            );

            pictureBox1->Invalidate();

            HandledMouseEventArgs^ he2 = safe_cast<HandledMouseEventArgs^>(e);
            he2->Handled = true;
        }

    private:
        void Panel1OnMouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            if ((Control::ModifierKeys & Keys::Control) == Keys::Control)
            {
                PerformZoom(e);
            }
        }

    private:
        void PictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
        {
            e->Graphics->Clear(Color::Gray);
            e->Graphics->ScaleTransform(zoomFactor, zoomFactor);
            e->Graphics->SmoothingMode = Drawing2D::SmoothingMode::None;
            e->Graphics->InterpolationMode = Drawing2D::InterpolationMode::NearestNeighbor;
            e->Graphics->PixelOffsetMode = Drawing2D::PixelOffsetMode::Half;
            e->Graphics->DrawImage(canvasBitmap, Point::Empty);

            e->Graphics->ResetTransform();

            if (zoomFactor >= 8)
                DrawPixelGrid(e->Graphics,
                    -(int)(panel2->AutoScrollPosition.X / zoomFactor),
                    -(int)(panel2->AutoScrollPosition.Y / zoomFactor),
                    canvasBitmap->Width,
                    canvasBitmap->Height);

            if (rendSelectionRect != Rectangle::Empty)
            {
                System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(Color::Black, 1);
                pen->DashStyle = Drawing2D::DashStyle::Dash;
                e->Graphics->DrawRectangle(pen, rendSelectionRect);
                delete pen;
            }

            if (activeBrush == ActiveBrush::Pasting && pastedPreview != nullptr)
            {
                System::Drawing::Rectangle renderRect = System::Drawing::Rectangle(
                    static_cast<int>(pastedPreviewLocation.X),
                    static_cast<int>(pastedPreviewLocation.Y),
                    static_cast<int>(pastedPreview->Width * zoomFactor),
                    static_cast<int>(pastedPreview->Height * zoomFactor)
                );
                e->Graphics->DrawImage(pastedPreview, renderRect);
                System::Drawing::Pen^ previewPen = gcnew System::Drawing::Pen(Color::LimeGreen, 1.0f);
                e->Graphics->DrawRectangle(previewPen, renderRect);
                delete previewPen;
            }

            if (selectedBrush == SelectedBrush::PickColor)
                DrawEyedropperPreview(e->Graphics);
        }

    private:
        void DrawPixelGrid(System::Drawing::Graphics^ g, int xStart, int yStart, int width, int height)
        {
            System::Drawing::Pen^ gridPen = gcnew System::Drawing::Pen(Color::FromArgb(60, 0, 0, 0));
            float scaledSize = zoomFactor;

            for (int x = xStart; x <= xStart + panel2->Size.Width / scaledSize; x++)
            {
                float px = x * scaledSize;
                g->DrawLine(gridPen, (int)px, 0, (int)px, (int)(yStart * scaledSize + panel2->Size.Height));
            }

            for (int y = yStart; y <= yStart + panel2->Size.Height / scaledSize; y++)
            {
                float py = y * scaledSize;
                g->DrawLine(gridPen, 0, (int)py, (int)(xStart * scaledSize + panel2->Width), (int)py);
            }

            delete gridPen;
        }

    private:
        void SelectToolMain(System::Object^ sender, System::EventArgs^ e)
        {
            ToolStripItem^ item = safe_cast<ToolStripItem^>(sender);

            DeselectEverything();

            String^ tag = safe_cast<String^>(item->Tag);

            if (tag == "PenMain")
            {
                selectedBrush = SelectedBrush::Draw;
                drawBrushSelectionTool->Checked = true;
                toolNameLabel->Text = "Перо";
            }
            else if (tag == "FloodFillMain")
            {
                selectedBrush = SelectedBrush::FloodFill;
                fillBrushSelectionTool->Checked = true;
                toolNameLabel->Text = "Заливка";
            }
            else if (tag == "PickColorMain")
            {
                selectedBrush = SelectedBrush::PickColor;
                pickBrushSelectionTool->Checked = true;
                toolNameLabel->Text = "Выбор цвета";
                activeBrush = ActiveBrush::ColorPicker;
            }
            else if (tag == "SelectionMain")
            {
                selectedBrush = SelectedBrush::Select;
                selectBrushSelectionTool->Checked = true;
                toolNameLabel->Text = "Выбрать";
            }
            else if (tag == "ClearMain")
            {
                selectedBrush = SelectedBrush::Clear;
                clearBrushSelectionTool->Checked = true;
                toolNameLabel->Text = "Ластик";
            }
            else if (tag == "BlendMain")
            {
                selectedBrush = SelectedBrush::Blend;
                blendBrushSelectionTool->Checked = true;
                toolNameLabel->Text = "Смешивание";
            }
        }

    private:
        void SelectToolProperty(System::Object^ sender, System::EventArgs^ e)
        {
            ToolStripItem^ item = safe_cast<ToolStripItem^>(sender);
            String^ tag = safe_cast<String^>(item->Tag);

            if (tag == "circleBrush")
            {
                selectedBrushType = SelectedBrushType::Circular;
                squareBrushSelector->Checked = false;
                circleBrushSelector->Checked = true;
            }
            else if (tag == "squareBrush")
            {
                selectedBrushType = SelectedBrushType::Rectangular;
                circleBrushSelector->Checked = false;
                squareBrushSelector->Checked = true;
            }
            else if (tag == "smoothBrush")
            {
                selectedSmoothType = smoothBrushSelector->Checked ? SelectedSmoothType::Smooth : SelectedSmoothType::Sharp;
            }
        }

    public:
        void DeselectEverything()
        {
            for each (System::Object ^ item in toolStrip1->Items)
            {
                ToolStripButton^ button = dynamic_cast<ToolStripButton^>(item);
                if (button != nullptr)
                    button->Checked = false;
            }
        }


    private:
        void CopyToClipboard()
        {
            if (canvasBitmap == nullptr || selectionRect.Width <= 0 || selectionRect.Height <= 0)
                return;

            System::Drawing::Rectangle srcRect = System::Drawing::Rectangle::Intersect(
                selectionRect,
                System::Drawing::Rectangle(0, 0, canvasBitmap->Width, canvasBitmap->Height)
            );

            if (srcRect.Width > 0 && srcRect.Height > 0)
            {
                System::Drawing::Bitmap^ copied = gcnew System::Drawing::Bitmap(srcRect.Width, srcRect.Height);
                {
                    System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(copied);
                    g->DrawImage(canvasBitmap, System::Drawing::Rectangle(0, 0, copied->Width, copied->Height), srcRect, System::Drawing::GraphicsUnit::Pixel);
                    delete g;
                }
                System::Windows::Forms::Clipboard::SetImage(copied);
                delete copied;
            }
        }

        void PasteImageFromClipboard()
        {
            if (!System::Windows::Forms::Clipboard::ContainsImage())
                return;

            System::Drawing::Image^ pastedImage = System::Windows::Forms::Clipboard::GetImage();
            if (pastedImage == nullptr) return;

            pastedPreview = gcnew System::Drawing::Bitmap(pastedImage);
            delete pastedImage;
            activeBrush = ActiveBrush::Pasting;

            System::Drawing::Point scroll = panel1->AutoScrollPosition;
            float x = (panel1->ClientSize.Width / 2 - scroll.X) / zoomFactor;
            float y = (panel1->ClientSize.Height / 2 - scroll.Y) / zoomFactor;

            pastedPreviewLocation = System::Drawing::Point((int)x, (int)y);

            activeBrush = ActiveBrush::Pasting;

            pictureBox1->Invalidate();
        }

        void copyToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            CopyToClipboard();
        }

        void pasteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            PasteImageFromClipboard();
        }

        void DrawLineBetween(System::Drawing::Point from, System::Drawing::Point to, System::Drawing::Color color)
        {
            int dx = to.X - from.X;
            int dy = to.Y - from.Y;
            int steps = Math::Max(System::Math::Abs(dx), System::Math::Abs(dy));
            if (steps == 0)
            {
                DrawAtPoint(from, color);
                return;
            }

            float stepX = dx / (float)steps;
            float stepY = dy / (float)steps;

            for (int i = 0; i <= steps; i++)
            {
                int x = (int)(from.X + i * stepX);
                int y = (int)(from.Y + i * stepY);
                DrawAtPoint(System::Drawing::Point(x, y), color);
            }
        }

        void DrawAtPoint(System::Drawing::Point pt, System::Drawing::Color color)
        {
            System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(canvasBitmap);
            {
                System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(color);
                g->SmoothingMode = (selectedSmoothType == SelectedSmoothType::Smooth) ? System::Drawing::Drawing2D::SmoothingMode::AntiAlias : System::Drawing::Drawing2D::SmoothingMode::None;
                g->FillEllipse(brush, pt.X - brushRadius, pt.Y - brushRadius, brushRadius * 2, brushRadius * 2);
                delete brush;
            }
            delete g;

            pictureBox1->Invalidate();
        }

    private:
        void DrawEyedropperPreview(System::Drawing::Graphics^ g)
        {
            int size = eyedropperRadius * 2 + 1;
            System::Drawing::Rectangle srcRect(
                eyedropperPosition.X - eyedropperRadius,
                eyedropperPosition.Y - eyedropperRadius,
                size, size);

            srcRect.Intersect(System::Drawing::Rectangle(0, 0, canvasBitmap->Width, canvasBitmap->Height));

            System::Drawing::Bitmap^ zoomed = gcnew System::Drawing::Bitmap(srcRect.Width, srcRect.Height);
            System::Drawing::Graphics^ gZoom = System::Drawing::Graphics::FromImage(zoomed);

            gZoom->DrawImage(canvasBitmap, System::Drawing::Rectangle(0, 0, zoomed->Width, zoomed->Height),
                srcRect, System::Drawing::GraphicsUnit::Pixel);

            int screenSize = size * eyedropperZoom;

            System::Drawing::Point clientPos = pictureBox1->PointToClient(System::Windows::Forms::Cursor::Position);
            int screenX = clientPos.X - screenSize / 2;
            int screenY = clientPos.Y - screenSize / 2;

            g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
            g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
            g->DrawImage(zoomed, System::Drawing::Rectangle(screenX, screenY, screenSize, screenSize));

            System::Drawing::Pen^ p = gcnew System::Drawing::Pen(System::Drawing::Color::Red, 1);
            g->DrawRectangle(p, screenX, screenY, screenSize, screenSize);
            g->DrawLine(p,
                screenX + screenSize / 2, screenY,
                screenX + screenSize / 2, screenY + screenSize);
            g->DrawLine(p,
                screenX, screenY + screenSize / 2,
                screenX + screenSize, screenY + screenSize / 2);

            delete p;
            delete gZoom;
            delete zoomed;
        }

        void deleteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(canvasBitmap);
            g->FillRectangle(BackColorBrush, selectionRect.X, selectionRect.Y, selectionRect.Width, selectionRect.Height);
            delete g;
            pictureBox1->Refresh();
        }

        void cutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            CopyToClipboard();
            deleteToolStripMenuItem_Click(sender, e);
        }

        void createNewToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            throw gcnew System::NotImplementedException();
        }

        void clearPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            canvasGraphics->Clear(SelectedBackColor);
            pictureBox1->Invalidate();
        }

        void increaseZoomToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            PerformZoom(gcnew System::Windows::Forms::HandledMouseEventArgs(System::Windows::Forms::MouseButtons::None, 0, 0, 0, 1));
        }

        void decreaseZoomToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            PerformZoom(gcnew System::Windows::Forms::HandledMouseEventArgs(System::Windows::Forms::MouseButtons::None, 0, 0, 0, -1));
        }

        void resetZoomToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            zoomFactor = 1;
            PerformZoom(gcnew System::Windows::Forms::HandledMouseEventArgs(System::Windows::Forms::MouseButtons::None, 0, 0, 0, -1));
        }

        void openExistingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                System::Drawing::Bitmap^ InnerBitmap;

                try
                {
                    InnerBitmap = gcnew System::Drawing::Bitmap(System::Drawing::Bitmap::FromFile(openFileDialog1->FileName));
                }
                catch (System::Exception^)
                {
                    System::Console::WriteLine("Ошибка загрузки файла");
                    return;
                }

                canvasBitmap = InnerBitmap;
                canvasGraphics = System::Drawing::Graphics::FromImage(canvasBitmap);
                canvasGraphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighQuality;
                pictureBox1->Image = canvasBitmap;
                pictureBox1->Focus();

                pictureBox1->Size = System::Drawing::Size((int)(canvasBitmap->Width * zoomFactor), (int)(canvasBitmap->Height * zoomFactor));
                pictureBox1->Invalidate();
            }
        }

        void saveAsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                canvasBitmap->Save(saveFileDialog1->FileName);
            }
        }

        void closeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }

        void accessSelectorBox_Leave(System::Object^ sender, System::EventArgs^ e)
        {
            int val = 0;
            System::Windows::Forms::ToolStripComboBox^ box = safe_cast<System::Windows::Forms::ToolStripComboBox^>(sender);
            if (System::Int32::TryParse(box->Text, val))
            {
                if (val > 100 || val < 0)
                {
                    System::Windows::Forms::MessageBox::Show("Введите значение от 0 до 100");
                    box->Focus();
                    return;
                }
                System::String^ tag = safe_cast<System::String^>(box->Tag);
                if (tag == "width")
                    brushRadius = val;
                else if (tag == "access")
                    access = val / 100.0f;
                else if (tag == "factor")
                    factor = val / 100.0f;
            }
            else
            {
                System::Windows::Forms::MessageBox::Show("Неверное значение.");
                box->Focus();
                return;
            }
        }



	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//

            this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::PictureBox1_Paint);

            canvasBitmap = gcnew System::Drawing::Bitmap(2000, 2000);

            canvasGraphics = System::Drawing::Graphics::FromImage(canvasBitmap);

            canvasGraphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighQuality;

            canvasGraphics->Clear(System::Drawing::Color::White);

            pictureBox1->Image = canvasBitmap;

            pictureBox1->Focus();

            pictureBox1->Size = System::Drawing::Size((int)(canvasBitmap->Width * zoomFactor), (int)(canvasBitmap->Height * zoomFactor));
            pictureBox1->Invalidate();

            SelectedBackColor = System::Drawing::Color::White;
            SelectedForeColor = System::Drawing::Color::Black;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
            System::ComponentModel::ComponentResourceManager^ resources = gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid);

            pictureBox1 = gcnew System::Windows::Forms::PictureBox();
            tabControl1 = gcnew System::Windows::Forms::TabControl();
            tabPage1 = gcnew System::Windows::Forms::TabPage();
            panel2 = gcnew System::Windows::Forms::Panel();
            menuStrip1 = gcnew System::Windows::Forms::MenuStrip();
            fileToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            createNewToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            openExistingToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            toolStripSeparator2 = gcnew System::Windows::Forms::ToolStripSeparator();
            saveAsToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            toolStripSeparator4 = gcnew System::Windows::Forms::ToolStripSeparator();
            closeToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            editToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            clearPictureToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            toolStripSeparator7 = gcnew System::Windows::Forms::ToolStripSeparator();
            cutToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            copyToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            pasteToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            deleteToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            viewToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            increaseZoomToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            decreaseZoomToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            resetZoomToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
            panel1 = gcnew System::Windows::Forms::Panel();
            toolStrip1 = gcnew System::Windows::Forms::ToolStrip();
            drawBrushSelectionTool = gcnew System::Windows::Forms::ToolStripButton();
            fillBrushSelectionTool = gcnew System::Windows::Forms::ToolStripButton();
            selectBrushSelectionTool = gcnew System::Windows::Forms::ToolStripButton();
            blendBrushSelectionTool = gcnew System::Windows::Forms::ToolStripButton();
            clearBrushSelectionTool = gcnew System::Windows::Forms::ToolStripButton();
            pickBrushSelectionTool = gcnew System::Windows::Forms::ToolStripButton();
            toolStripSeparator1 = gcnew System::Windows::Forms::ToolStripSeparator();
            toolStripButton8 = gcnew System::Windows::Forms::ToolStripButton();
            toolStripButton9 = gcnew System::Windows::Forms::ToolStripButton();
            colorDialog1 = gcnew System::Windows::Forms::ColorDialog();
            toolStrip2 = gcnew System::Windows::Forms::ToolStrip();
            toolNameLabel = gcnew System::Windows::Forms::ToolStripLabel();
            toolStripSeparator6 = gcnew System::Windows::Forms::ToolStripSeparator();
            circleBrushSelector = gcnew System::Windows::Forms::ToolStripButton();
            squareBrushSelector = gcnew System::Windows::Forms::ToolStripButton();
            smoothBrushSelector = gcnew System::Windows::Forms::ToolStripButton();
            toolStripSeparator5 = gcnew System::Windows::Forms::ToolStripSeparator();
            toolStripLabel2 = gcnew System::Windows::Forms::ToolStripLabel();
            widthSelectorBox = gcnew System::Windows::Forms::ToolStripComboBox();
            toolStripSeparator8 = gcnew System::Windows::Forms::ToolStripSeparator();
            toolStripLabel3 = gcnew System::Windows::Forms::ToolStripLabel();
            accessSelectorBox = gcnew System::Windows::Forms::ToolStripComboBox();
            toolStripSeparator9 = gcnew System::Windows::Forms::ToolStripSeparator();
            toolStripLabel4 = gcnew System::Windows::Forms::ToolStripLabel();
            factorSelectorBox = gcnew System::Windows::Forms::ToolStripComboBox();
            openFileDialog1 = gcnew System::Windows::Forms::OpenFileDialog();
            saveFileDialog1 = gcnew System::Windows::Forms::SaveFileDialog();

            // Begin Init pictureBox1
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pictureBox1))->BeginInit();

            tabControl1->SuspendLayout();
            tabPage1->SuspendLayout();
            panel2->SuspendLayout();
            menuStrip1->SuspendLayout();
            panel1->SuspendLayout();
            toolStrip1->SuspendLayout();
            toolStrip2->SuspendLayout();

            this->SuspendLayout();

            // pictureBox1
            pictureBox1->BackColor = System::Drawing::Color::Gray;
            pictureBox1->Location = System::Drawing::Point(0, 0);
            pictureBox1->Name = "pictureBox1";
            pictureBox1->Size = System::Drawing::Size(871, 487);
            pictureBox1->TabIndex = 0;
            pictureBox1->TabStop = false;
            pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseDown);
            pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseMove);
            pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseUp);
            pictureBox1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Panel1OnMouseWheel);

            // tabControl1
            tabControl1->Controls->Add(tabPage1);
            tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
            tabControl1->Location = System::Drawing::Point(35, 49);
            tabControl1->Name = "tabControl1";
            tabControl1->SelectedIndex = 0;
            tabControl1->Size = System::Drawing::Size(885, 521);
            tabControl1->TabIndex = 1;

            // tabPage1
            tabPage1->AutoScroll = true;
            tabPage1->Controls->Add(panel2);
            tabPage1->Location = System::Drawing::Point(4, 24);
            tabPage1->Name = "tabPage1";
            tabPage1->Padding = System::Windows::Forms::Padding(3);
            tabPage1->Size = System::Drawing::Size(877, 493);
            tabPage1->TabIndex = 0;
            tabPage1->Text = "tabPage1";
            tabPage1->UseVisualStyleBackColor = true;

            // panel2
            panel2->AutoScroll = true;
            panel2->BackColor = System::Drawing::Color::DimGray;
            panel2->Controls->Add(pictureBox1);
            panel2->Dock = System::Windows::Forms::DockStyle::Fill;
            panel2->Location = System::Drawing::Point(3, 3);
            panel2->Name = "panel2";
            panel2->Size = System::Drawing::Size(871, 487);
            panel2->TabIndex = 0;

            // menuStrip1
            menuStrip1->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^> {
                fileToolStripMenuItem, editToolStripMenuItem, viewToolStripMenuItem
            });
            menuStrip1->Location = System::Drawing::Point(0, 0);
            menuStrip1->Name = "menuStrip1";
            menuStrip1->Size = System::Drawing::Size(920, 24);
            menuStrip1->TabIndex = 2;
            menuStrip1->Text = "menuStrip1";

            // fileToolStripMenuItem
            fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^> {
                createNewToolStripMenuItem, openExistingToolStripMenuItem, toolStripSeparator2,
                    saveAsToolStripMenuItem, toolStripSeparator4, closeToolStripMenuItem
            });
            fileToolStripMenuItem->Name = "fileToolStripMenuItem";
            fileToolStripMenuItem->Size = System::Drawing::Size(48, 20);
            fileToolStripMenuItem->Text = "Файл";

            // createNewToolStripMenuItem
            createNewToolStripMenuItem->Name = "createNewToolStripMenuItem";
            createNewToolStripMenuItem->Size = System::Drawing::Size(163, 22);
            createNewToolStripMenuItem->Text = "Создать...";
            createNewToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::createNewToolStripMenuItem_Click);

            // openExistingToolStripMenuItem
            openExistingToolStripMenuItem->Name = "openExistingToolStripMenuItem";
            openExistingToolStripMenuItem->Size = System::Drawing::Size(163, 22);
            openExistingToolStripMenuItem->Text = "Открыть...";
            openExistingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openExistingToolStripMenuItem_Click);

            // toolStripSeparator2
            toolStripSeparator2->Name = "toolStripSeparator2";
            toolStripSeparator2->Size = System::Drawing::Size(160, 6);

            // saveAsToolStripMenuItem
            saveAsToolStripMenuItem->Name = "saveAsToolStripMenuItem";
            saveAsToolStripMenuItem->Size = System::Drawing::Size(163, 22);
            saveAsToolStripMenuItem->Text = "Сохранить как...";
            saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveAsToolStripMenuItem_Click);

            // toolStripSeparator4
            toolStripSeparator4->Name = "toolStripSeparator4";
            toolStripSeparator4->Size = System::Drawing::Size(160, 6);

            // closeToolStripMenuItem
            closeToolStripMenuItem->Name = "closeToolStripMenuItem";
            closeToolStripMenuItem->Size = System::Drawing::Size(163, 22);
            closeToolStripMenuItem->Text = "Закрыть";
            closeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::closeToolStripMenuItem_Click);

            // editToolStripMenuItem
            editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^> {
                clearPictureToolStripMenuItem, toolStripSeparator7, cutToolStripMenuItem,
                    copyToolStripMenuItem, pasteToolStripMenuItem, deleteToolStripMenuItem
            });
            editToolStripMenuItem->Name = "editToolStripMenuItem";
            editToolStripMenuItem->Size = System::Drawing::Size(59, 20);
            editToolStripMenuItem->Text = "Правка";

            // clearPictureToolStripMenuItem
            clearPictureToolStripMenuItem->Name = "clearPictureToolStripMenuItem";
            clearPictureToolStripMenuItem->Size = System::Drawing::Size(203, 22);
            clearPictureToolStripMenuItem->Text = "Очистить изображение";
            clearPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::clearPictureToolStripMenuItem_Click);

            // toolStripSeparator7
            toolStripSeparator7->Name = "toolStripSeparator7";
            toolStripSeparator7->Size = System::Drawing::Size(200, 6);

            // cutToolStripMenuItem
            cutToolStripMenuItem->Name = "cutToolStripMenuItem";
            cutToolStripMenuItem->Size = System::Drawing::Size(203, 22);
            cutToolStripMenuItem->Text = "Вырезать";
            cutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::cutToolStripMenuItem_Click);

            // copyToolStripMenuItem
            copyToolStripMenuItem->Name = "copyToolStripMenuItem";
            copyToolStripMenuItem->Size = System::Drawing::Size(203, 22);
            copyToolStripMenuItem->Text = "Копировать";
            copyToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::copyToolStripMenuItem_Click);

            // pasteToolStripMenuItem
            pasteToolStripMenuItem->Name = "pasteToolStripMenuItem";
            pasteToolStripMenuItem->Size = System::Drawing::Size(203, 22);
            pasteToolStripMenuItem->Text = "Вставить";
            pasteToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::pasteToolStripMenuItem_Click);

            // deleteToolStripMenuItem
            deleteToolStripMenuItem->Name = "deleteToolStripMenuItem";
            deleteToolStripMenuItem->Size = System::Drawing::Size(203, 22);
            deleteToolStripMenuItem->Text = "Удалить";
            deleteToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deleteToolStripMenuItem_Click);

            // viewToolStripMenuItem
            viewToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^> {
                increaseZoomToolStripMenuItem, decreaseZoomToolStripMenuItem, resetZoomToolStripMenuItem
            });
            viewToolStripMenuItem->Name = "viewToolStripMenuItem";
            viewToolStripMenuItem->Size = System::Drawing::Size(39, 20);
            viewToolStripMenuItem->Text = "Вид";

            // increaseZoomToolStripMenuItem
            increaseZoomToolStripMenuItem->Name = "increaseZoomToolStripMenuItem";
            increaseZoomToolStripMenuItem->Size = System::Drawing::Size(191, 22);
            increaseZoomToolStripMenuItem->Text = "Увеличить масшаб";
            increaseZoomToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::increaseZoomToolStripMenuItem_Click);

            // decreaseZoomToolStripMenuItem
            decreaseZoomToolStripMenuItem->Name = "decreaseZoomToolStripMenuItem";
            decreaseZoomToolStripMenuItem->Size = System::Drawing::Size(191, 22);
            decreaseZoomToolStripMenuItem->Text = "Уменьшить масштаб";
            decreaseZoomToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::decreaseZoomToolStripMenuItem_Click);

            // resetZoomToolStripMenuItem
            resetZoomToolStripMenuItem->Name = "resetZoomToolStripMenuItem";
            resetZoomToolStripMenuItem->Size = System::Drawing::Size(191, 22);
            resetZoomToolStripMenuItem->Text = "Сбросить масшаб";
            resetZoomToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::resetZoomToolStripMenuItem_Click);

            // panel1
            panel1->Controls->Add(toolStrip1);
            panel1->Dock = System::Windows::Forms::DockStyle::Left;
            panel1->Location = System::Drawing::Point(0, 24);
            panel1->Name = "panel1";
            panel1->Size = System::Drawing::Size(35, 546);
            panel1->TabIndex = 3;

            // toolStrip1
            toolStrip1->Dock = System::Windows::Forms::DockStyle::Fill;
            toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
            toolStrip1->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^> {
                drawBrushSelectionTool, fillBrushSelectionTool, selectBrushSelectionTool,
                    blendBrushSelectionTool, clearBrushSelectionTool, pickBrushSelectionTool,
                    toolStripSeparator1, toolStripButton8, toolStripButton9
            });
            toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
            toolStrip1->Location = System::Drawing::Point(0, 0);
            toolStrip1->Name = "toolStrip1";
            toolStrip1->Padding = System::Windows::Forms::Padding(0, 10, 1, 0);
            toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
            toolStrip1->Size = System::Drawing::Size(35, 546);
            toolStrip1->TabIndex = 0;
            toolStrip1->Text = "toolStrip1";

            // drawBrushSelectionTool
            drawBrushSelectionTool->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            drawBrushSelectionTool->Image = Bitmap::FromFile("Resources/pen.png");
            drawBrushSelectionTool->ImageTransparentColor = System::Drawing::Color::Magenta;
            drawBrushSelectionTool->Margin = System::Windows::Forms::Padding(0, 2, 0, 2);
            drawBrushSelectionTool->Name = "drawBrushSelectionTool";
            drawBrushSelectionTool->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
            drawBrushSelectionTool->Size = System::Drawing::Size(33, 25);
            drawBrushSelectionTool->Tag = "PenMain";
            drawBrushSelectionTool->Text = "toolStripButton2";
            drawBrushSelectionTool->ToolTipText = "drawBrushSelectionTool";
            drawBrushSelectionTool->Click += gcnew System::EventHandler(this, &Form1::SelectToolMain);

            // fillBrushSelectionTool
            fillBrushSelectionTool->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            fillBrushSelectionTool->Image = Bitmap::FromFile("Resources/floodFill.png");
            fillBrushSelectionTool->ImageTransparentColor = System::Drawing::Color::Magenta;
            fillBrushSelectionTool->Margin = System::Windows::Forms::Padding(0, 2, 0, 2);
            fillBrushSelectionTool->Name = "fillBrushSelectionTool";
            fillBrushSelectionTool->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
            fillBrushSelectionTool->Size = System::Drawing::Size(33, 25);
            fillBrushSelectionTool->Tag = "FloodFillMain";
            fillBrushSelectionTool->Text = "toolStripButton4";
            fillBrushSelectionTool->Click += gcnew System::EventHandler(this, &Form1::SelectToolMain);

            // selectBrushSelectionTool
            selectBrushSelectionTool->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            selectBrushSelectionTool->Image = Bitmap::FromFile("Resources/selection_box.png");
            selectBrushSelectionTool->ImageTransparentColor = System::Drawing::Color::Magenta;
            selectBrushSelectionTool->Margin = System::Windows::Forms::Padding(0, 2, 0, 2);
            selectBrushSelectionTool->Name = "selectBrushSelectionTool";
            selectBrushSelectionTool->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
            selectBrushSelectionTool->Size = System::Drawing::Size(33, 25);
            selectBrushSelectionTool->Tag = "SelectionMain";
            selectBrushSelectionTool->Text = "toolStripButton5";
            selectBrushSelectionTool->Click += gcnew System::EventHandler(this, &Form1::SelectToolMain);

            // blendBrushSelectionTool
            blendBrushSelectionTool->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            blendBrushSelectionTool->Image = Bitmap::FromFile("Resources/blend.png");
            blendBrushSelectionTool->ImageTransparentColor = System::Drawing::Color::Magenta;
            blendBrushSelectionTool->Margin = System::Windows::Forms::Padding(0, 2, 0, 2);
            blendBrushSelectionTool->Name = "blendBrushSelectionTool";
            blendBrushSelectionTool->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
            blendBrushSelectionTool->Size = System::Drawing::Size(33, 25);
            blendBrushSelectionTool->Tag = "BlendMain";
            blendBrushSelectionTool->Text = "toolStripButton6";
            blendBrushSelectionTool->Click += gcnew System::EventHandler(this, &Form1::SelectToolMain);

            // clearBrushSelectionTool
            clearBrushSelectionTool->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            clearBrushSelectionTool->Image = Bitmap::FromFile("Resources/clear_format.png");
            clearBrushSelectionTool->ImageTransparentColor = System::Drawing::Color::Magenta;
            clearBrushSelectionTool->Margin = System::Windows::Forms::Padding(0, 2, 0, 2);
            clearBrushSelectionTool->Name = "clearBrushSelectionTool";
            clearBrushSelectionTool->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
            clearBrushSelectionTool->Size = System::Drawing::Size(33, 25);
            clearBrushSelectionTool->Tag = "ClearMain";
            clearBrushSelectionTool->Text = "toolStripButton7";
            clearBrushSelectionTool->Click += gcnew System::EventHandler(this, &Form1::SelectToolMain);

            // pickBrushSelectionTool
            pickBrushSelectionTool->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            pickBrushSelectionTool->Image = Bitmap::FromFile("Resources/color_picker.png");
            pickBrushSelectionTool->ImageTransparentColor = System::Drawing::Color::Magenta;
            pickBrushSelectionTool->Margin = System::Windows::Forms::Padding(0, 2, 0, 2);
            pickBrushSelectionTool->Name = "pickBrushSelectionTool";
            pickBrushSelectionTool->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
            pickBrushSelectionTool->Size = System::Drawing::Size(33, 25);
            pickBrushSelectionTool->Tag = "PickColorMain";
            pickBrushSelectionTool->Text = "toolStripButton3";
            pickBrushSelectionTool->Click += gcnew System::EventHandler(this, &Form1::SelectToolMain);

            // toolStripSeparator1
            toolStripSeparator1->Name = "toolStripSeparator1";
            toolStripSeparator1->Size = System::Drawing::Size(33, 6);

            // toolStripButton8
            toolStripButton8->AutoSize = false;
            toolStripButton8->AutoToolTip = false;
            toolStripButton8->BackColor = System::Drawing::Color::Black;
            toolStripButton8->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::None;
            toolStripButton8->ImageTransparentColor = System::Drawing::Color::Magenta;
            toolStripButton8->Margin = System::Windows::Forms::Padding(0, 6, 0, 2);
            toolStripButton8->Name = "toolStripButton8";
            toolStripButton8->Size = System::Drawing::Size(20, 20);
            toolStripButton8->Text = "toolStripButton8";
            toolStripButton8->Click += gcnew System::EventHandler(this, &Form1::toolStripButton8_Click);
            toolStripButton8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::toolStripButton8_MouseDown);
            
            // toolStripButton9
            toolStripButton9->AutoSize = false;
            toolStripButton9->BackColor = System::Drawing::Color::White;
            toolStripButton9->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::None;
            toolStripButton9->ImageTransparentColor = System::Drawing::Color::Magenta;
            toolStripButton9->Margin = System::Windows::Forms::Padding(3, 5, 0, 2);
            toolStripButton9->Name = "toolStripButton9";
            toolStripButton9->Size = System::Drawing::Size(20, 20);
            toolStripButton9->Text = "toolStripButton8";
            toolStripButton9->Click += gcnew System::EventHandler(this, &Form1::toolStripButton9_Click);

            // colorDialog1
            colorDialog1->AnyColor = true;
            colorDialog1->FullOpen = true;

            // toolStrip2
            toolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
            toolStrip2->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>{
                toolNameLabel, toolStripSeparator6, circleBrushSelector, squareBrushSelector, smoothBrushSelector,
                    toolStripSeparator5, toolStripLabel2, widthSelectorBox, toolStripSeparator8, toolStripLabel3,
                    accessSelectorBox, toolStripSeparator9, toolStripLabel4, factorSelectorBox
            });
            toolStrip2->Location = System::Drawing::Point(35, 24);
            toolStrip2->Name = "toolStrip2";
            toolStrip2->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
            toolStrip2->Size = System::Drawing::Size(885, 25);
            toolStrip2->TabIndex = 4;
            toolStrip2->Text = "toolStrip2";

            // toolNameLabel
            toolNameLabel->AutoSize = false;
            toolNameLabel->BackColor = System::Drawing::Color::Transparent;
            toolNameLabel->Margin = System::Windows::Forms::Padding(10, 0, 0, 0);
            toolNameLabel->Name = "toolNameLabel";
            toolNameLabel->Size = System::Drawing::Size(150, 22);
            toolNameLabel->Text = "Пусто";
            toolNameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

            // toolStripSeparator6
            toolStripSeparator6->Name = "toolStripSeparator6";
            toolStripSeparator6->Size = System::Drawing::Size(6, 25);

            // circleBrushSelector
            circleBrushSelector->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            circleBrushSelector->Image = Bitmap::FromFile("Resources/dry_clean.png");
            circleBrushSelector->ImageTransparentColor = System::Drawing::Color::Magenta;
            circleBrushSelector->Name = "circleBrushSelector";
            circleBrushSelector->Size = System::Drawing::Size(23, 22);
            circleBrushSelector->Tag = "circleBrush";
            circleBrushSelector->Text = "toolStripButton10";
            circleBrushSelector->Click += gcnew System::EventHandler(this, &Form1::SelectToolProperty);

            // squareBrushSelector
            squareBrushSelector->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            squareBrushSelector->Image = Bitmap::FromFile("Resources/stop.png");
            squareBrushSelector->ImageTransparentColor = System::Drawing::Color::Magenta;
            squareBrushSelector->Name = "squareBrushSelector";
            squareBrushSelector->Size = System::Drawing::Size(23, 22);
            squareBrushSelector->Tag = "squareBrush";
            squareBrushSelector->Text = "toolStripButton1";
            squareBrushSelector->Click += gcnew System::EventHandler(this, &Form1::SelectToolProperty);

            // smoothBrushSelector
            smoothBrushSelector->CheckOnClick = true;
            smoothBrushSelector->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            smoothBrushSelector->Image = Bitmap::FromFile("Resources/shape.png");
            smoothBrushSelector->ImageTransparentColor = System::Drawing::Color::Magenta;
            smoothBrushSelector->Name = "smoothBrushSelector";
            smoothBrushSelector->Size = System::Drawing::Size(23, 22);
            smoothBrushSelector->Tag = "smoothBrush";
            smoothBrushSelector->Text = "toolStripButton11";
            smoothBrushSelector->Click += gcnew System::EventHandler(this, &Form1::SelectToolProperty);

            // toolStripSeparator5
            toolStripSeparator5->Name = "toolStripSeparator5";
            toolStripSeparator5->Size = System::Drawing::Size(6, 25);

            // toolStripLabel2
            toolStripLabel2->BackColor = System::Drawing::Color::Transparent;
            toolStripLabel2->Margin = System::Windows::Forms::Padding(10, 1, 0, 2);
            toolStripLabel2->Name = "toolStripLabel2";
            toolStripLabel2->Size = System::Drawing::Size(58, 22);
            toolStripLabel2->Text = "Толщина";

            // widthSelectorBox
            widthSelectorBox->Margin = System::Windows::Forms::Padding(0, 0, 1, 0);
            widthSelectorBox->Name = "widthSelectorBox";
            widthSelectorBox->Size = System::Drawing::Size(75, 25);
            widthSelectorBox->Tag = "width";
            widthSelectorBox->Text = "10";
            widthSelectorBox->Leave += gcnew System::EventHandler(this, &Form1::accessSelectorBox_Leave);

            // toolStripSeparator8
            toolStripSeparator8->Name = "toolStripSeparator8";
            toolStripSeparator8->Size = System::Drawing::Size(6, 25);

            // toolStripLabel3
            toolStripLabel3->BackColor = System::Drawing::Color::Transparent;
            toolStripLabel3->Margin = System::Windows::Forms::Padding(10, 1, 0, 2);
            toolStripLabel3->Name = "toolStripLabel3";
            toolStripLabel3->Size = System::Drawing::Size(47, 22);
            toolStripLabel3->Text = "Допуск";

            // accessSelectorBox
            accessSelectorBox->Name = "accessSelectorBox";
            accessSelectorBox->Size = System::Drawing::Size(75, 25);
            accessSelectorBox->Tag = "access";
            accessSelectorBox->Text = "5";
            accessSelectorBox->Leave += gcnew System::EventHandler(this, &Form1::accessSelectorBox_Leave);

            // toolStripSeparator9
            toolStripSeparator9->Name = "toolStripSeparator9";
            toolStripSeparator9->Size = System::Drawing::Size(6, 25);

            // toolStripLabel4
            toolStripLabel4->BackColor = System::Drawing::Color::Transparent;
            toolStripLabel4->Margin = System::Windows::Forms::Padding(10, 1, 0, 2);
            toolStripLabel4->Name = "toolStripLabel4";
            toolStripLabel4->Size = System::Drawing::Size(47, 22);
            toolStripLabel4->Text = "Фактор";

            // factorSelectorBox
            factorSelectorBox->Name = "factorSelectorBox";
            factorSelectorBox->Size = System::Drawing::Size(75, 25);
            factorSelectorBox->Tag = "factor";
            factorSelectorBox->Text = "5";
            factorSelectorBox->Leave += gcnew System::EventHandler(this, &Form1::accessSelectorBox_Leave);

            // openFileDialog1
            openFileDialog1->FileName = "openFileDialog1";

            this->AutoScaleDimensions = System::Drawing::SizeF(7.0F, 15.0F);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::Silver;
            this->ClientSize = System::Drawing::Size(920, 570);
            this->Controls->Add(tabControl1);
            this->Controls->Add(toolStrip2);
            this->Controls->Add(panel1);
            this->Controls->Add(menuStrip1);
            this->DoubleBuffered = true;
            this->MainMenuStrip = menuStrip1;
            this->Name = "Form1";
            this->Text = "Редактор изображений";
            this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(pictureBox1))->EndInit();

            tabControl1->ResumeLayout(false);
            tabPage1->ResumeLayout(false);
            panel2->ResumeLayout(false);
            menuStrip1->ResumeLayout(false);
            menuStrip1->PerformLayout();
            panel1->ResumeLayout(false);
            panel1->PerformLayout();
            toolStrip1->ResumeLayout(false);
            toolStrip1->PerformLayout();
            toolStrip2->ResumeLayout(false);
            toolStrip2->PerformLayout();

            this->ResumeLayout(false);
            this->PerformLayout();
		}
#pragma endregion



    
};
}
