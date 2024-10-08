#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>

#include "fmt/format.h"
#include "fmt/ranges.h"
// using namespace fmt::literals;  // just to make the format literals visible

#include <string>
#include <vector>

#include "hd/hd_keypress.hpp"

#include <numbers> // for pi
using namespace std::numbers;

struct point_3d {
    double x, y, z;
};

void write_polyline(const std::string& fname, const std::vector<point_3d>& v)
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

int main()
{
    size_t num_pts{101};
    size_t num_tpts{51};

    std::vector<point_3d> v3d(num_pts);

    double const lambda = 1; // wavelength [m]

    double const dx = 2 * lambda / (num_pts - 1);

    double const k = 2 * pi / lambda; // wavenumber

    double const f = 1; // [Hz]
    double const omega = 2 * pi * f;

    double const T = 1. / f;
    double const dt = T / num_tpts;

    // double const c = lambda * f; // Ausbreitungsgeschwindigkeit der Welle [m/s]
    double const ampl = 1.;

    for (size_t l = 0; l < num_tpts; ++l) {
        double t = l * dt;

        for (size_t i = 0; i < num_pts; ++i) {
            double x = i * dx;
            v3d[i].x = x;
            v3d[i].y = ampl * sin(k * x - omega * t);
            v3d[i].z = 0;
        }

        std::string fname = fmt::format("test{:04}.vtp", l);
        write_polyline(fname, v3d);
    }

    hd::cmdl_wait_for_enter();

    return EXIT_SUCCESS;
}