// Spline.h: interface for the CSpline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINE_H__E4B987FD_0798_424F_9D92_B5CA8CA37F17__INCLUDED_)
#define AFX_SPLINE_H__E4B987FD_0798_424F_9D92_B5CA8CA37F17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

namespace dxfv
{

class CSpline  : public cDXFGraphObject
{
public:
    std::string m_Layer;
    int m_FitPointCount;
    int m_ControlPointCount;
    double x[MAXPOINTS],y[MAXPOINTS];
    unsigned char m_Select;
    unsigned char m_Nest;

    CSpline();
    CSpline( cCodeValue& cv );
    virtual ~CSpline();
    bool Append( cvit_t& cvit );
    bool Read( FILE * fp, int& code, char* value );
    void Update( cBoundingRectangle& rect );

    /**  get wxWidgets drawing parameters, scaled to display window, for the 'next' line

    @param[in/out] draw  structure holding parameters, intialize index to zero on first call
    @return true if valid line has been returned

    */
    bool getDraw( cDrawPrimitiveData& draw );

#ifdef wxwbuild
    void Draw( wxDC& dc, CDxf * dxf );
#endif // wxwbuild
#ifdef nanabuild
    void Draw( nana::paint::graphics& graph, CDxf * dxf );
#endif // nanabuild

    void wxwidgets( bool f = true )
    {
        myfwxwidgets = f;
    }

    void Options( CDxf * dxf );

private:
    bool myfwxwidgets;          ///< true if using wxwidgets method for control points
    std::vector<float> Ax;
    std::vector<float> Ay;
    std::vector<float> Bx;
    std::vector<float> By;
    std::vector<float> Cx;
    std::vector<float> Cy;

    void Generate();
    void MatrixSolve(std::vector<float>& B,
                     std::vector< std::vector<float> >& Mat );
    bool getDrawControlPoint( cDrawPrimitiveData& draw );
    void QuadraticBezierInterpolation(
        double& x, double& y,
        int index,
        float f );
};

}

#endif // !defined(AFX_SPLINE_H__E4B987FD_0798_424F_9D92_B5CA8CA37F17__INCLUDED_)
