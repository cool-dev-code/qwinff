/*  This file is part of QWinFF, a media converter GUI.

    QWinFF is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 or 3 of the License.

    QWinFF is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QWinFF.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "filepathoperations.h"
#include <QCoreApplication>

FilePathOperations::FilePathOperations()
{
}

QString FilePathOperations::GenerateUniqueFileName(const QDir& output_dir, const QString& input_file_basename
                               , const QString& ext, const QSet<QString>& extra)
{
    int filename_index = 1;
    QString result;
    do {
        // The index part of the file
        QString str_index("");
        if (filename_index > 1) {
            // If the index is larger than 1, append -index to the filename.
            str_index = QString("-%1").arg(filename_index);
        }

        // Fill in output filename.
        result =
                output_dir.absoluteFilePath(input_file_basename)   // filename
                + str_index                                        // index
                + '.'                                              // point
                + ext;                                             // extension

        ++filename_index;
    } while (QFileInfo(result).exists()
             || extra.contains(result)); // If file(n) exists, try file(n+1).
    return result;
}

QString FilePathOperations::GenerateUniqueFileName(const QString &filename, const QSet<QString>& extra)
{
    QDir dir = QFileInfo(filename).dir();
    QString basename = QFileInfo(filename).completeBaseName();
    QString ext = QFileInfo(filename).suffix();
    return GenerateUniqueFileName(dir, basename, ext, extra);
}

QString FilePathOperations::GenerateTempFileName(const QString& filename)
{
    QString result;
    do {
        // Generate temporary file name.
        result = QString("%1-%2-temp-%3.%4").arg(filename)
                .arg(qrand()).arg(QCoreApplication::applicationPid())
                .arg(QFileInfo(filename).suffix());
    } while (QFileInfo(result).exists()); // Regenerate if exists.

    return result;
}
