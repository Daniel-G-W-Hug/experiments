#include "output.hpp"

#include "fmt/format.h"
#include "fmt/ranges.h"

#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>

namespace hd {

void write_polyline(std::string const& fname, std::vector<point_3d> const& v);

void write_polyline(std::string const& fname, std::vector<point_3d> const& v)
{
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    for (size_t i = 0; i < v.size(); ++i) {
        points->InsertNextPoint(v[i].x, v[i].y, v[i].z);
    }

    // Create a cell array to store the lines in and add the lines to it
    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();

    for (size_t i = 1; i < v.size(); ++i) {
        vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
        line->GetPointIds()->SetId(0, i - 1);
        line->GetPointIds()->SetId(1, i);
        lines->InsertNextCell(line);
    }

    // Create a polydata object and add the points to it.
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    // Add the lines to the dataset
    polydata->SetLines(lines);

    // Write the file
    vtkSmartPointer<vtkXMLPolyDataWriter> writer =
        vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName(fname.c_str());
    writer->SetInputData(polydata);

    // Optional - set the mode. The default is binary.
    // writer->SetDataModeToBinary();
    // writer->SetDataModeToAscii();

    writer->Write();
}

void write_to_file(output_t const otype, size_t nt, std::vector<double> const& x,
                   std::vector<double> const& u)
{

    switch (otype) {

        case output_t::none: {
            break;
        }

        case output_t::print: {
            fmt::print("nt = {}\n", nt);
            fmt::print("u [ {:.4} ]\n\n", fmt::join(u, ", "));
            break;
        }

        case output_t::vtp: {
            // fmt::print("nt = {}\n", nt);
            size_t n = u.size();
            // fmt::print("n = {}\n", n);
            std::vector<point_3d> v3d(n);

            for (size_t i = 0; i < n; ++i) {
                v3d[i].x = x[i];
                v3d[i].y = u[i];
                v3d[i].z = 0.0;
            }
            std::string fn = fmt::format("file{:04}.vtp", nt);
            write_polyline(fn, v3d);
        }

    } // switch(otype)
}

} // namespace hd
