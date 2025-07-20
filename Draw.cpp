#include "Draw.h"



Draw::Draw()
{

}
Draw::~Draw()
{
    delete(regular24);
    delete(bold28);
    wglDeleteContext(new_context);
}
void Draw::Render(HDC& hDc)
{
    CreateContext(hDc);
    RestoreContext(hDc);
}
//void Draw::CreateContext(HDC& hDc)
//{
//
//    static GLint last_viewport[4];
//
//    static bool init = false;
//
//    if (!init)
//    {
//        gladLoadGL();
//        //moved from every frame
//        old_context = wglGetCurrentContext();
//        glGetIntegerv(GL_VIEWPORT, viewport);
//        screenProportions.x = viewport[2] / 640.0f;
//        screenProportions.y = viewport[3] / 480.0f;
//        screenCenter.x = viewport[2] / 2;
//        screenCenter.y = viewport[3] / 2;
//        //moved from every frame
//
//        if (new_context != NULL)
//        {
//            wglMakeCurrent(hDc, NULL);
//            wglDeleteContext(new_context);
//        }
//
//        new_context = wglCreateContext(hDc);
//
//        wglMakeCurrent(hDc, new_context);
//
//        glViewport(0, 0, viewport[2], viewport[3]);
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//        glDisable(GL_DEPTH_TEST);
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        memcpy(last_viewport, viewport, sizeof(GLint) * 4);
//        regular24 = new Font(24, 0, 0, "Calibri", hDc);
//        bold28 = new Font(28, true, 0, "Calibri", hDc);
//        init = true;
//    }
//    CalculateScreenAdjustment();
//    wglMakeCurrent(hDc, new_context);
//}

bool Draw::CreateContext(HDC& hDc) 
{
    static GLint last_viewport[4] = { 0, 0, 0, 0 };
    static bool init = false;

    if (!init) 
    {
        gladLoadGL();

        old_context = wglGetCurrentContext();

        if (new_context) {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(new_context);
        }

        new_context = wglCreateContext(hDc);


        if (!new_context || !wglMakeCurrent(hDc, new_context)) {
            return false;
        }

        glGetIntegerv(GL_VIEWPORT, viewport);


        //test
        if (viewport[0] == 0 && viewport[1] == 0 && viewport[2] == 0 && viewport[3] == 0)
        {
            if (!a)
                return false;
            else
            {
                viewport[2] = *(int*)(a->fovX - 8);  viewport[3] = *(int*)(a->fovX - 4);
            }
        }
        //test

        screenProportions.x = viewport[2] / 640.0f;
        screenProportions.y = viewport[3] / 480.0f;
        screenCenter.x = viewport[2] / 2;
        screenCenter.y = viewport[3] / 2;

        glViewport(0, 0, viewport[2], viewport[3]);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        memcpy(last_viewport, viewport, sizeof(GLint) * 4);

        regular24 = new Font(24, 0, 0, "Calibri", hDc);
        bold28 = new Font(28, true, 0, "Calibri", hDc);

        init = true;
    }

    CalculateScreenAdjustment();

    if (!wglMakeCurrent(hDc, new_context)) 
    {

    }

    return true;
}
void Draw::CalculateScreenAdjustment()
{
    fovAdjustment.x = tan(refDef.fov.x * 0.5f * DEGREE_TO_RAD);
    fovAdjustment.y = tan(refDef.fov.y * 0.5f * DEGREE_TO_RAD);
}
void Draw::Init(Addresses*_a)
{
    a = _a;
    refDef = *(RefDef*)a->fovX;
    CalculateScreenAdjustment();

}
void Draw::DrawMenuItem(MenuItem&item)
{
    std::string strToDraw = item.GetTotalString();
    if (!strToDraw.empty())
        regular24->Print(item.loc.x, item.loc.y, item.color, strToDraw.c_str());
}
void Draw::DrawMenuBlock(MenuBlock& mb)
{
    Vertex2 l_top, r_top, l_bot, r_bot;

    l_top = mb.loc;

    r_top.x = l_top.x + mb.width;   r_top.y = l_top.y;
    r_bot.x = l_top.x + mb.width;   r_bot.y = l_top.y + mb.height;
    l_bot.x = l_top.x;           l_bot.y = l_top.y + mb.height;

    bold28->Print(mb.titlePos.x, mb.titlePos.y, RGB::red, mb.title);

    if (isMenuOpen)
    {
        if (mb.IsHovered(mouseCrd))
        {
            //transparent when hovered over
            mb.color[3] = 0.1;
            //disable menu
            short keyHeld = GetAsyncKeyState(VK_SPACE);
            if ((keyHeld & 1) && (keyHeld & 0x8000))
            {
                mb.isDraw = !mb.isDraw;

            }

            if (GetAsyncKeyState(0x4D)& 0x8000)
            {
                mb.loc.x = mouseCrd.x  - (mb.width/2);
                mb.loc.y = mouseCrd.y  - (mb.height/4);
            }
        }
        else
            mb.color[3] = 0.4;


    }

    glColor4f(mb.color[0], mb.color[1], mb.color[2], mb.color[3]);
    glBegin(GL_QUADS);
    glVertex2i(l_bot.x, l_bot.y);
    glVertex2i(r_bot.x, r_bot.y);
    glVertex2i(r_top.x, r_top.y);
    glVertex2i(l_top.x, l_top.y);
    glEnd();



    mb.SetBlockSize(true);
    if (!mb.isDraw)
        return;
    for (int i = 0; i < mb.items.size(); i++)
    {
        DrawMenuItem(mb.items[i]);
    }
}
void Draw::DrawUI(UI&ui)
{
    mouseCrd = *(Vec2*)a->mousePinterCrd;
    mouseCrd.x *= screenProportions.x;
    mouseCrd.y *= screenProportions.y;

    isMenuOpen = *(bool*)a->consoleOpen;

    for (auto& mb : ui.menuBlocks)
    {
        DrawMenuBlock(mb.second);
    }

}
void Draw::DrawFilledPolygon(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p4, const GLfloat color[4])
{
    Vertex2 p1_2d, p2_2d, p3_2d, p4_2d;

    if (!WTS(p1, p1_2d) || !WTS(p2, p2_2d) || !WTS(p3, p3_2d) || !WTS(p4, p4_2d))
        return;

    glBegin(GL_TRIANGLES);
    glColor4f(color[0], color[1], color[2], color[3]);
    glVertex2i(p1_2d.x, p1_2d.y);
    glVertex2i(p2_2d.x, p2_2d.y);
    glVertex2i(p3_2d.x, p3_2d.y);

    glVertex2i(p3_2d.x,p3_2d.y);
    glVertex2i(p4_2d.x,p4_2d.y);
    glVertex2i(p1_2d.x,p1_2d.y);
    glEnd();
}
void Draw::RestoreContext(HDC& hDc)
{
    wglMakeCurrent(hDc, old_context);
    glDisable(GL_BLEND);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}
void Draw::DrawTrajectory(const std::vector<Vec3>&vertices, const float&lineWidth, const GLfloat color[4])
{
    if (vertices.empty())
        return;
    Vertex2 prevPoint;
    Vertex2 point2d;
    WTS(vertices[0], prevPoint);
    for (int i = 1; i < vertices.size(); i++)
    {
        if (WTS(vertices[i], point2d) && prevPoint != 0)          
        {
            glLineWidth(lineWidth);
            glBegin(GL_LINES);
            glColor4f(color[0], color[1], color[2], color[3]);
            glVertex2f(prevPoint.x, prevPoint.y);
            glVertex2f(point2d.x, point2d.y);
            glEnd();
        }
        prevPoint = point2d;
    }
}
void Draw::DrawRotatedBBox(const Vec3& _bottom, const Vec3& _top, const Vec3& min,
    const Vec3& max, const float&yaw, const float& lineWidth, const GLfloat color[4])
{
    Vertex2 bottom[4];
    Vertex2 top[4];

    float cosPhi = cos(yaw * DEGREE_TO_RAD); float sinPhi = sin(yaw * DEGREE_TO_RAD);
    //float cosPhiN = cos(-yaw * DEGREE_TO_RAD); float sinPhiN = sin(-yaw * DEGREE_TO_RAD);

    Vec3 xp_yp; xp_yp.x += -min.x; xp_yp.y += -min.y; xp_yp.z += min.z;
    Vec3 xp_yn; xp_yn.x += -min.x; xp_yn.y += min.y;  xp_yn.z += min.z;
    Vec3 xn_yp; xn_yp.x += min.x;  xn_yp.y += -min.y; xn_yp.z += min.z;
    Vec3 xn_yn; xn_yn.x += min.x;  xn_yn.y += min.y;  xn_yn.z += min.z;

    Vec3 xp_ypz; xp_ypz.x += max.x;  xp_ypz.y += max.y;  xp_ypz.z += max.z;
    Vec3 xp_ynz; xp_ynz.x += max.x;  xp_ynz.y += -max.y; xp_ynz.z += max.z;
    Vec3 xn_ypz; xn_ypz.x += -max.x; xn_ypz.y += max.y;  xn_ypz.z += max.z;
    Vec3 xn_ynz; xn_ynz.x += -max.x; xn_ynz.y += -max.y; xn_ynz.z += max.z;

    Vec3 xp_ypT = xp_yp, xp_ynT = xp_yn, xn_ypT = xn_yp, xn_ynT = xn_yn, xp_ypzT = xp_ypz, xp_ynzT = xp_ynz, xn_ypzT = xn_ypz, xn_ynzT = xn_ynz;

    xp_ypT.x = xp_yp.x * cosPhi - xp_yp.y * sinPhi;
    xp_ypT.y = xp_yp.x * sinPhi + xp_yp.y * cosPhi;

    xp_ynT.x = xp_yn.x * cosPhi - xp_yn.y * sinPhi; //wr
    xp_ynT.y = xp_yn.x * sinPhi + xp_yn.y * cosPhi;

    xn_ypT.x = xn_yp.x * cosPhi - xn_yp.y * sinPhi; //wr
    xn_ypT.y = xn_yp.x * sinPhi + xn_yp.y * cosPhi;

    xn_ynT.x = xn_yn.x * cosPhi - xn_yn.y * sinPhi;
    xn_ynT.y = xn_yn.x * sinPhi + xn_yn.y * cosPhi;

    //z
    xp_ypzT.x = xp_ypz.x * cosPhi - xp_ypz.y * sinPhi;
    xp_ypzT.y = xp_ypz.x * sinPhi + xp_ypz.y * cosPhi;
                                      
    xp_ynzT.x = xp_ynz.x * cosPhi - xp_ynz.y * sinPhi; //wr
    xp_ynzT.y = xp_ynz.x * sinPhi + xp_ynz.y * cosPhi;
                                      
    xn_ypzT.x = xn_ypz.x * cosPhi - xn_ypz.y * sinPhi; //wr
    xn_ypzT.y = xn_ypz.x * sinPhi + xn_ypz.y * cosPhi;
                                       
    xn_ynzT.x = xn_ynz.x * cosPhi - xn_ynz.y * sinPhi;
    xn_ynzT.y = xn_ynz.x * sinPhi + xn_ynz.y * cosPhi;

    xp_ypT = xp_ypT + _bottom;
    xp_ynT = xp_ynT + _bottom;
    xn_ypT = xn_ypT + _bottom;
    xn_ynT = xn_ynT + _bottom;

    xp_ypzT = xp_ypzT + _top;
    xp_ynzT = xp_ynzT + _top;
    xn_ypzT = xn_ypzT + _top;
    xn_ynzT = xn_ynzT + _top;


    if (!WTS(xn_ynT, bottom[0]) || !WTS(xp_ynT, bottom[1]) || !WTS(xp_ypT, bottom[2]) || !WTS(xn_ypT, bottom[3]))
        return;
    if (!WTS(xn_ynzT, top[0]) || !WTS(xp_ynzT, top[1]) || !WTS(xp_ypzT, top[2]) || !WTS(xn_ypzT, top[3]))
        return;


    glLineWidth(1);
    glBegin(GL_LINES);
    glColor4f(color[0], color[1], color[2], color[3]);

    //bottom
    glVertex2f(bottom[0].x, bottom[0].y);
    glVertex2f(bottom[1].x, bottom[1].y);

    glVertex2f(bottom[1].x, bottom[1].y);
    glVertex2f(bottom[2].x, bottom[2].y);

    glVertex2f(bottom[2].x, bottom[2].y);
    glVertex2f(bottom[3].x, bottom[3].y);

    glVertex2f(bottom[3].x, bottom[3].y);
    glVertex2f(bottom[0].x, bottom[0].y);

    //middle
    glVertex2f(bottom[0].x, bottom[0].y);
    glVertex2f(top[0].x, top[0].y);

    glVertex2f(bottom[1].x, bottom[1].y);
    glVertex2f(top[1].x, top[1].y);

    glVertex2f(bottom[2].x, bottom[2].y);
    glVertex2f(top[2].x, top[2].y);

    glVertex2f(bottom[3].x, bottom[3].y);
    glVertex2f(top[3].x, top[3].y);

    //top
    glVertex2f(top[0].x, top[0].y);
    glVertex2f(top[1].x, top[1].y);

    glVertex2f(top[1].x, top[1].y);
    glVertex2f(top[2].x, top[2].y);

    glVertex2f(top[2].x, top[2].y);
    glVertex2f(top[3].x, top[3].y);

    glVertex2f(top[3].x, top[3].y);
    glVertex2f(top[0].x, top[0].y);

    glEnd();
}
void Draw::DrawBBox(const Vec3& _bottom, const Vec3& _top, const Vec3& min, const Vec3& max, const float& lineWidth, const GLfloat color[4])
{

    Vertex2 bottom[4];
    Vertex2 top[4];

    Vec3 xp_yp; xp_yp = _bottom;  xp_yp.x += -min.x; xp_yp.y += -min.y; xp_yp.z += min.z;
    Vec3 xp_yn; xp_yn = _bottom;  xp_yn.x += -min.x; xp_yn.y += min.y;  xp_yn.z += min.z;
    Vec3 xn_yp; xn_yp = _bottom;  xn_yp.x += min.x;  xn_yp.y += -min.y; xn_yp.z += min.z;
    Vec3 xn_yn; xn_yn = _bottom;  xn_yn.x += min.x;  xn_yn.y += min.y;  xn_yn.z += min.z;

    Vec3 xp_ypz; xp_ypz = _top; xp_ypz.x += max.x;  xp_ypz.y += max.y;  xp_ypz.z += max.z;
    Vec3 xp_ynz; xp_ynz = _top; xp_ynz.x += max.x;  xp_ynz.y += -max.y; xp_ynz.z += max.z;
    Vec3 xn_ypz; xn_ypz = _top; xn_ypz.x += -max.x; xn_ypz.y += max.y;  xn_ypz.z += max.z;
    Vec3 xn_ynz; xn_ynz = _top; xn_ynz.x += -max.x; xn_ynz.y += -max.y; xn_ynz.z += max.z;

    Vec3 xpypznR;
    Vec3 xpynznR;
    Vec3 xnypznR;
    Vec3 xnynznR;

    Vec3 xpypzpR;
    Vec3 xpynzpR;
    Vec3 xnypzpR;
    Vec3 xnynzpR;


    if (!WTS(xn_yn, bottom[0]) || !WTS(xp_yn, bottom[1]) || !WTS(xp_yp, bottom[2]) || !WTS(xn_yp, bottom[3]))
        return;
    if (!WTS(xn_ynz, top[0]) || !WTS(xp_ynz, top[1]) || !WTS(xp_ypz, top[2]) || !WTS(xn_ypz, top[3]))
        return;


    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glColor4f(color[0], color[1], color[2], color[3]);

    //bottom
    glVertex2f(bottom[0].x, bottom[0].y);
    glVertex2f(bottom[1].x, bottom[1].y);

    glVertex2f(bottom[1].x, bottom[1].y);
    glVertex2f(bottom[2].x, bottom[2].y);

    glVertex2f(bottom[2].x, bottom[2].y);
    glVertex2f(bottom[3].x, bottom[3].y);

    glVertex2f(bottom[3].x, bottom[3].y);
    glVertex2f(bottom[0].x, bottom[0].y);

    //middle
    glVertex2f(bottom[0].x, bottom[0].y);
    glVertex2f(top[0].x, top[0].y);

    glVertex2f(bottom[1].x, bottom[1].y);
    glVertex2f(top[1].x, top[1].y);

    glVertex2f(bottom[2].x, bottom[2].y);
    glVertex2f(top[2].x, top[2].y);

    glVertex2f(bottom[3].x, bottom[3].y);
    glVertex2f(top[3].x, top[3].y);

    //top
    glVertex2f(top[0].x, top[0].y);
    glVertex2f(top[1].x, top[1].y);

    glVertex2f(top[1].x, top[1].y);
    glVertex2f(top[2].x, top[2].y);

    glVertex2f(top[2].x, top[2].y);
    glVertex2f(top[3].x, top[3].y);

    glVertex2f(top[3].x, top[3].y);
    glVertex2f(top[0].x, top[0].y);

    glEnd();
}
void Draw::DrawLine(const Vec3& start, const Vec3& end, const float& lineWidth, const GLfloat color[4])
{
    Vertex2 st;
    Vertex2 en; 

    if (!WTS(start, st))
        return;
    if (!WTS(end, en))
        return;

    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glColor4f(color[0], color[1], color[2], color[3]);
    glVertex2f(st.x, st.y);
    glVertex2f(en.x, en.y);
    glEnd();
}
void Draw::DrawLine(const Vertex2& start, const Vertex2& end, const float& lineWidth, const GLfloat color[4])
{
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glColor4f(color[0], color[1], color[2], color[3]);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
    glEnd();
}
void Draw::DrawFilledBox(const std::vector<Vertex2>&vertices, const GLfloat color[4])
{
    glBegin(GL_POLYGON);
    glColor4f(color[0], color[1], color[2], color[3]);

    glBegin(GL_POLYGON);
    glVertex2i(vertices[0].x, vertices[0].y);
    glVertex2i(vertices[1].x, vertices[1].y);
    glVertex2i(vertices[2].x, vertices[2].y);
    glVertex2i(vertices[3].x, vertices[3].y);

    glEnd();
}
void Draw::DrawLineFigure(std::vector<Vec3>& points, const float& lineWidth, const GLfloat color[4])
{
    std::vector<Vertex2> verticesToDraw(points.size());

    for (int i = 0; i < points.size(); i++)
    {
        WTS(points[i], verticesToDraw[i]);
    }

    for (int i = 0; i < verticesToDraw.size(); i++)
    {
        if (i < verticesToDraw.size() - 1)
        {
            glLineWidth(lineWidth);
            glBegin(GL_LINES);
            glColor4f(color[0], color[1], color[2], color[3]);
            glVertex2f(verticesToDraw[i].x, verticesToDraw[i].y);
            glVertex2f(verticesToDraw[i+1].x, verticesToDraw[i+1].y);
            glEnd();
        }
        else
        {
            glLineWidth(lineWidth);
            glBegin(GL_LINES);
            glColor4f(color[0], color[1], color[2], color[3]);
            glVertex2f(verticesToDraw[i].x, verticesToDraw[i].y);
            glVertex2f(verticesToDraw[0].x, verticesToDraw[0].y);
            glEnd();
        }
    }
}
void Draw::DrawLineFigure(const std::vector<Vertex2>& screenPoints, const float& lineWidth, const GLfloat color[4])
{
    for (int i = 0; i < screenPoints.size(); i++)
    {
        if (i < screenPoints.size() - 1)
        {
            if (screenPoints[i] == 0 || screenPoints[i + 1] == 0)
                continue;

            glLineWidth(lineWidth);
            glBegin(GL_LINES);
            glColor4f(color[0], color[1], color[2], color[3]);
            glVertex2f(screenPoints[i].x, screenPoints[i].y);
            glVertex2f(screenPoints[i + 1].x, screenPoints[i + 1].y);
            glEnd();
        }
        else
        {
            if (screenPoints[i] == 0 || screenPoints[0] == 0)
                continue;

            glLineWidth(lineWidth);
            glBegin(GL_LINES);
            glColor4f(color[0], color[1], color[2], color[3]);
            glVertex2f(screenPoints[i].x, screenPoints[i].y);
            glVertex2f(screenPoints[0].x, screenPoints[0].y);
            glEnd();
        }
    }
}
void Draw::GetScreenFigurePoints(const std::vector<Vec3>& points, std::vector<Vertex2>& screenPoints)
{
    screenPoints.resize(points.size());
    for (int i = 0; i < points.size(); i++)
    {
        WTS(points[i], screenPoints[i]);
    }
}
bool Draw::WTS(const Vec3& worldPoint, Vertex2& screenPoint)
{
    Vec3	local, transformed;

    local = worldPoint - refDef.cameraPos;

    transformed.x = vecs::DotProduct(local, refDef.vright);
    transformed.y = vecs::DotProduct(local, refDef.vup);
    transformed.z = vecs::DotProduct(local, refDef.vfwd);

    if (transformed.z < 0.1)
    {
        screenPoint.x = 0; screenPoint.y = 0;
        return false;
    }

    float xzi = -screenCenter.x / (transformed.z * fovAdjustment.x);
    float yzi = screenCenter.y / (transformed.z * fovAdjustment.y);

    screenPoint.x = (screenCenter.x + xzi * transformed.x);
    screenPoint.y = (screenCenter.y - yzi * transformed.y);

    return true;
}
bool Draw::WTSrotated(const Vec3& point, Vertex2& result, const Vertex2& rotateRelativeTo)
{
    Vec3	local, transformed;

    local = point - refDef.cameraPos;

    transformed.x = vecs::DotProduct(local, refDef.vright);
    transformed.y = vecs::DotProduct(local, refDef.vup);
    transformed.z = vecs::DotProduct(local, refDef.vfwd);

    if (transformed.z > 0.1)
    {
        float xzi = -screenCenter.x / (transformed.z * fovAdjustment.x);
        float yzi = screenCenter.y / (transformed.z * fovAdjustment.y);

        result.x = (screenCenter.x + xzi * transformed.x);
        result.y = (screenCenter.y - yzi * transformed.y);

        return false;
    }

    float xzi = -screenCenter.x / (transformed.z * fovAdjustment.x);
    float yzi = screenCenter.y / (transformed.z * fovAdjustment.y);

    result.x = (screenCenter.x + xzi * transformed.x);
    result.y = (screenCenter.y - yzi * transformed.y);

    Vertex2 intermediate = rotateRelativeTo - result;
    result = rotateRelativeTo + intermediate;

    return true;
}
void Draw::CreateCircle(const float&radius, const int&numSegments,std::vector<Vec3>& points)
{
    float minAngle = (2 * PI) / numSegments;

    float currentAngle = 0;
    for (int i = 0; i < numSegments; i++)
    {
        currentAngle = i * minAngle;
        Vec3 point{0,0,0}; point.x += cos(currentAngle) * radius;  point.y += sin(currentAngle) * radius;
        points.push_back(point);
    }
}
void Draw::TransformFigure(const Vec3& origin, std::vector<Vec3>& points, const Vec3& normal)
{
    Vec3 right, up;
    Vec3 upRef = (std::fabs(normal.z) == 1) ? Vec3{ 1, 0, 0 } : Vec3{ 0, 0, 1 }; //WORKS

    right = vecs::NormalizeVector(vecs::CrossProduct(normal, upRef));
    up = vecs::NormalizeVector(vecs::CrossProduct(right, normal));

    for (auto& v : points) { v = { 
        origin.x + v.x * right.x + v.y * up.x + v.z * normal.x, 
        origin.y + v.x * right.y + v.y * up.y + v.z * normal.y,
        origin.z + v.x * right.z + v.y * up.z + v.z * normal.z }; }
}
void Draw::DrawImpactFigure(const Vec3& finalPoint, const Vec3& normal, const float&radius, GLfloat color[4])
{
    float internalRadius = radius*0.85f;
    float numSengments = 32; //must be equal

    std::vector<Vec3> externalCircle; std::vector<Vertex2> externalCircleScreen;
    CreateCircle(radius, numSengments, externalCircle);
    TransformFigure(finalPoint, externalCircle, normal);
    GetScreenFigurePoints(externalCircle, externalCircleScreen);
    DrawLineFigure(externalCircleScreen, 2, color);



    std::vector<Vec3> internalCircle; std::vector<Vertex2> internalCircleScreen;
    CreateCircle(internalRadius, numSengments, internalCircle); for (auto& p : internalCircle) { p.z += radius*0.15; }
    TransformFigure(finalPoint, internalCircle, normal);
    GetScreenFigurePoints(internalCircle, internalCircleScreen);
    //DrawLineFigure(internalCircleScreen, 1, color);

    std::vector<Vec3> internalCircleHalo; std::vector<Vertex2> internalCircleHaloScreen;
    CreateCircle(internalRadius, numSengments, internalCircleHalo); for (auto& p : internalCircleHalo) { p.z += radius * 0.45; }
    TransformFigure(finalPoint, internalCircleHalo, normal);
    GetScreenFigurePoints(internalCircleHalo, internalCircleHaloScreen);
    DrawLineFigure(internalCircleHaloScreen, 1, color);
    //return;
    std::vector<Vertex2> verts(4);



    for (int i = 0; i < externalCircleScreen.size(); i+=2)
    {
        if (i < externalCircleScreen.size() - 1 
            && externalCircleScreen[i] != 0
            && externalCircleScreen[i + 1] != 0
            && internalCircleScreen[i + 1] != 0
            && internalCircleScreen[i] != 0
            )
        {
            verts[0] = externalCircleScreen[i];
            verts[1] = externalCircleScreen[i + 1];
            verts[2] = internalCircleScreen[i+1];
            verts[3] = internalCircleScreen[i];

            DrawFilledBox(verts, color);
        }
    }

    for (int i = 0; i < internalCircleScreen.size(); i++)
    {
        if (i < internalCircleScreen.size() - 1
            && internalCircleHaloScreen[i] != 0
            && internalCircleHaloScreen[i + 1] != 0
            && internalCircleScreen[i + 1] != 0
            && internalCircleScreen[i] != 0
            )
        {

            verts[0] = internalCircleHaloScreen[i];
            verts[1] = internalCircleHaloScreen[i + 1];
            verts[2] = internalCircleScreen[i + 1];
            verts[3] = internalCircleScreen[i];
            DrawFilledBox(verts, color);
        }
        else
        {
            if (internalCircleHaloScreen[i] != 0
                && internalCircleHaloScreen[0] != 0
                && internalCircleScreen[0] != 0
                && internalCircleScreen[i] !=0
                && i == internalCircleScreen.size() - 1
                )
            {
                verts[0] = internalCircleHaloScreen[i];
                verts[1] = internalCircleHaloScreen[0];
                verts[2] = internalCircleScreen[0];
                verts[3] = internalCircleScreen[i];
                DrawFilledBox(verts, color);
            }
        }
        color[3] = 0.15;
    }
}

void Draw::DrawWorld(World* world, const Vec3& origin, const CellCoordinates& myLocation, const CellCoordinates& myFactualLocation, std::unordered_map<MeshColors, std::vector<float>>& meshColors) 
{
    if (world == nullptr)
        return;

    GLfloat color[4] = { 1,1,1,1 };

    Vec3 xn_yn;
    Vec3 xp_yn;
    Vec3 xn_yp;
    Vec3 xp_yp;

    Vec3 xn_ynz;
    Vec3 xp_ynz;
    Vec3 xn_ypz;
    Vec3 xp_ypz;

    Vertex2 bottom[4];
    Vertex2 top[4];

    float cellEdge = 0.3;
    float radiusToDrawStuff = 2400;
    float transparencyLimit = 100;

    Chunk* currentChunk = nullptr;

    bool isMyCellDrawn = false;

    float myZpos = world->get_cell_float_coordinates_from_location(myFactualLocation).z;


    for (auto& chLoc : world->validChunks)
    {
        currentChunk = world->chunks[chLoc];
        if (vecs::VecDistance(currentChunk->locationFloat, origin) > radiusToDrawStuff)
            continue;
        for (auto& cellLocation : currentChunk->validCells)
        {
            Cell* cell = world->get_cell(cellLocation.chunkLocation, cellLocation.cellLocation);
            if (cell == nullptr)
                continue;

            Vec3 center = cell->GetCenter();
            float distanceToCell = vecs::VecDistance(center, origin);
            if (distanceToCell > radiusToDrawStuff / 2)
                continue;

            if (cell->flags & CellFlags::IS_EDGE)
            {
                color[0] = meshColors[MeshColors::EDGE_COLOR][0]; color[1] = meshColors[MeshColors::EDGE_COLOR][1];
                color[2] = meshColors[MeshColors::EDGE_COLOR][2]; color[3] = meshColors[MeshColors::EDGE_COLOR][3];
            }
            else if (cell->flags & CellFlags::IS_EDGE2)
            {
                color[0] = meshColors[MeshColors::EDGE2_COLOR][0]; color[1] = meshColors[MeshColors::EDGE2_COLOR][1];
                color[2] = meshColors[MeshColors::EDGE2_COLOR][2]; color[3] = meshColors[MeshColors::EDGE2_COLOR][3];
            }
            else if (cell->flags & CellFlags::IS_EDGE3)
            {
                color[0] = meshColors[MeshColors::EDGE3_COLOR][0]; color[1] = meshColors[MeshColors::EDGE3_COLOR][1];
                color[2] = meshColors[MeshColors::EDGE3_COLOR][2]; color[3] = meshColors[MeshColors::EDGE3_COLOR][3];
            }
            else if (cell->flags & CellFlags::WALKABLE)
            {
                color[0] = meshColors[MeshColors::WALKABLE_COLOR][0]; color[1] = meshColors[MeshColors::WALKABLE_COLOR][1];
                color[2] = meshColors[MeshColors::WALKABLE_COLOR][2]; color[3] = meshColors[MeshColors::WALKABLE_COLOR][3];
            }
            if (cell->flags & CellFlags::IS_MOVER)
            {
                color[0] = meshColors[MeshColors::MOVER_COLOR][0]; color[1] = meshColors[MeshColors::MOVER_COLOR][1];
                color[2] = meshColors[MeshColors::MOVER_COLOR][2]; color[3] = meshColors[MeshColors::MOVER_COLOR][3];
            }
            if (cell->flags & CellFlags::IS_BANNED)
            {
                color[0] = meshColors[MeshColors::BANNED_COLOR][0]; color[1] = meshColors[MeshColors::BANNED_COLOR][1];
                color[2] = meshColors[MeshColors::BANNED_COLOR][2]; color[3] = meshColors[MeshColors::BANNED_COLOR][3];
            }
            if (cell->flags & CellFlags::IS_JUMP)
            {
                color[0] = meshColors[MeshColors::JUMP_CELL_COLOR][0]; color[1] = meshColors[MeshColors::JUMP_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::JUMP_CELL_COLOR][2]; color[3] = meshColors[MeshColors::JUMP_CELL_COLOR][3];
            }
            else if (cell->flags & CellFlags::IS_WALKABLE_UP)
            {
                color[0] = meshColors[MeshColors::UP_PNLY_CELL_COLOR][0]; color[1] = meshColors[MeshColors::UP_PNLY_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::UP_PNLY_CELL_COLOR][2]; color[3] = meshColors[MeshColors::UP_PNLY_CELL_COLOR][3];
            }
            else if (cell->flags & CellFlags::IS_WALKABLE_DOWN)
            {
                color[0] = meshColors[MeshColors::DOWN_PNLY_CELL_COLOR][0]; color[1] = meshColors[MeshColors::DOWN_PNLY_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::DOWN_PNLY_CELL_COLOR][2]; color[3] = meshColors[MeshColors::DOWN_PNLY_CELL_COLOR][3];
            }
            else if (cell->flags & CellFlags::IS_WALKABLE_UP)
            {
                color[0] = meshColors[MeshColors::UP_PNLY_CELL_COLOR][0]; color[1] = meshColors[MeshColors::UP_PNLY_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::UP_PNLY_CELL_COLOR][2]; color[3] = meshColors[MeshColors::UP_PNLY_CELL_COLOR][3];
            }
            else if (cell->flags & CellFlags::IS_ELEVATOR_BRIDGE)
            {
                color[0] = meshColors[MeshColors::BRIDGE_CELL_COLOR][0]; color[1] = meshColors[MeshColors::BRIDGE_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::BRIDGE_CELL_COLOR][2]; color[3] = meshColors[MeshColors::BRIDGE_CELL_COLOR][3];
            }
            else if (cell->flags & CellFlags::IS_ELEVATOR_COLUMN)
            {
                color[0] = meshColors[MeshColors::COLUMN_CELL_COLOR][0]; color[1] = meshColors[MeshColors::COLUMN_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::COLUMN_CELL_COLOR][2]; color[3] = meshColors[MeshColors::COLUMN_CELL_COLOR][3];
            }
            else if (cell->flags & CellFlags::IS_HIGHCOST)
            {
                color[0] = meshColors[MeshColors::HIGHCOST_CELL_COLOR][0]; color[1] = meshColors[MeshColors::HIGHCOST_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::HIGHCOST_CELL_COLOR][2]; color[3] = meshColors[MeshColors::HIGHCOST_CELL_COLOR][3];
            }
            else if (cell->flags & (CellFlags::IS_ELEVATOR_BUTTON_1))
            {
                color[0] = meshColors[MeshColors::ELEVATOR_BUTTON_CELL_COLOR][0]; color[1] = meshColors[MeshColors::ELEVATOR_BUTTON_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::ELEVATOR_BUTTON_CELL_COLOR][2]; color[3] = meshColors[MeshColors::ELEVATOR_BUTTON_CELL_COLOR][3];
            }
            else if (cell->flags & (CellFlags::IS_ELEVATOR_BUTTON_2))
            {
                color[0] = meshColors[MeshColors::ELEVATOR_BUTTON_2_CELL_COLOR][0]; color[1] = meshColors[MeshColors::ELEVATOR_BUTTON_2_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::ELEVATOR_BUTTON_2_CELL_COLOR][2]; color[3] = meshColors[MeshColors::ELEVATOR_BUTTON_2_CELL_COLOR][3];
            }
            else if (cell->flags & (CellFlags::IS_ELEVATOR_BUTTON_CALL))
            {
                color[0] = meshColors[MeshColors::ELEVATOR_BUTTON_CALL_CELL_COLOR][0]; color[1] = meshColors[MeshColors::ELEVATOR_BUTTON_CALL_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::ELEVATOR_BUTTON_CALL_CELL_COLOR][2]; color[3] = meshColors[MeshColors::ELEVATOR_BUTTON_CALL_CELL_COLOR][3];
            }
            else if (cell->flags & (CellFlags::IS_ELEVATOR_DETECTOR | CellFlags::IS_ELEVATOR_DETECTOR_UP))
            {
                color[0] = meshColors[MeshColors::ELEVATOR_CELL_COLOR][0]; color[1] = meshColors[MeshColors::ELEVATOR_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::ELEVATOR_CELL_COLOR][2]; color[3] = meshColors[MeshColors::ELEVATOR_CELL_COLOR][3];
            }
            else if (cell->graphNode == nullptr && !(cell->flags & CellFlags::IS_BANNED))
            {
                memcpy(color, RGB::black, sizeof(color));
            }
            if ((cell->flags & (CellFlags::IS_RESCANNED | CellFlags::REFRESH)) || (currentChunk->flags & ChunkFlags::REFRESH_THIS_CHUNK))
            {
                memcpy(color, RGB::white, sizeof(color));
            }
            if (cell->entNum > 1023)
            {
                memcpy(color, RGB::cyan, sizeof(color));
            }

            if (abs(myZpos - center.z) > transparencyLimit)
                color[3] = 0.04;

            //if (currentChunk->flags & ChunkFlags::IS_VISITED_BY_BOT)
            //{
            //    memcpy(color, RGB::cyan, sizeof(color));
            //}


            //if (cell->flags & CellFlags::IS_MOVER)
            //    memcpy(color, RGB::yellow, sizeof(RGB::yellow));

            //if (myCell == cell)
            //    memcpy(color, RGB::green, sizeof(RGB::yellow));
            if (myLocation.chunkLocation == currentChunk->index && myLocation.cellLocation == cell->loc)
            {
                isMyCellDrawn = true;
                color[0] = meshColors[MeshColors::MY_CELL_COLOR][0]; color[1] = meshColors[MeshColors::MY_CELL_COLOR][1];
                color[2] = meshColors[MeshColors::MY_CELL_COLOR][2]; color[3] = meshColors[MeshColors::MY_CELL_COLOR][3];
            }


#ifdef DRAW_CUBED_MESH

            xn_yn = center - WorldConstants::HALF_CELL_SIZE; xn_yn.x += cellEdge; xn_yn.y += cellEdge;
            xp_yn.x = center.x + WorldConstants::HALF_CELL_SIZE - cellEdge; xp_yn.y = center.y - WorldConstants::HALF_CELL_SIZE + cellEdge; xp_yn.z = center.z - WorldConstants::HALF_CELL_SIZE;
            xn_yp.x = center.x - WorldConstants::HALF_CELL_SIZE + cellEdge; xn_yp.y = center.y + WorldConstants::HALF_CELL_SIZE - cellEdge; xn_yp.z = center.z - WorldConstants::HALF_CELL_SIZE;
            xp_yp.x = center.x + WorldConstants::HALF_CELL_SIZE - cellEdge; xp_yp.y = center.y + WorldConstants::HALF_CELL_SIZE - cellEdge; xp_yp.z = center.z - WorldConstants::HALF_CELL_SIZE;

            xn_ynz = xn_yn; xn_ynz.z = center.z + WorldConstants::HALF_CELL_SIZE;
            xp_ynz = xp_yn; xp_ynz.z = center.z + WorldConstants::HALF_CELL_SIZE;
            xn_ypz = xn_yp; xn_ypz.z = center.z + WorldConstants::HALF_CELL_SIZE;
            xp_ypz = xp_yp; xp_ypz.z = center.z + WorldConstants::HALF_CELL_SIZE;

            if (!WTS(xn_yn, bottom[0]) || !WTS(xp_yn, bottom[1]) || !WTS(xp_yp, bottom[2]) || !WTS(xn_yp, bottom[3]))
                continue;
            if (!WTS(xn_ynz, top[0]) || !WTS(xp_ynz, top[1]) || !WTS(xp_ypz, top[2]) || !WTS(xn_ypz, top[3]))
                continue;

            glLineWidth(1);
            glBegin(GL_LINES);
            glColor4f(color[0], color[1], color[2], color[3]);

            //bottom
            glVertex2f(bottom[0].x, bottom[0].y);
            glVertex2f(bottom[1].x, bottom[1].y);

            glVertex2f(bottom[1].x, bottom[1].y);
            glVertex2f(bottom[2].x, bottom[2].y);

            glVertex2f(bottom[2].x, bottom[2].y);
            glVertex2f(bottom[3].x, bottom[3].y);

            glVertex2f(bottom[3].x, bottom[3].y);
            glVertex2f(bottom[0].x, bottom[0].y);

            //middle
            glVertex2f(bottom[0].x, bottom[0].y);
            glVertex2f(top[0].x, top[0].y);

            glVertex2f(bottom[1].x, bottom[1].y);
            glVertex2f(top[1].x, top[1].y);

            glVertex2f(bottom[2].x, bottom[2].y);
            glVertex2f(top[2].x, top[2].y);

            glVertex2f(bottom[3].x, bottom[3].y);
            glVertex2f(top[3].x, top[3].y);

            //top
            glVertex2f(top[0].x, top[0].y);
            glVertex2f(top[1].x, top[1].y);

            glVertex2f(top[1].x, top[1].y);
            glVertex2f(top[2].x, top[2].y);

            glVertex2f(top[2].x, top[2].y);
            glVertex2f(top[3].x, top[3].y);

            glVertex2f(top[3].x, top[3].y);
            glVertex2f(top[0].x, top[0].y);

            glEnd();

#endif // DRAW_CUBED_MESH

#ifdef DRAW_FLAT_MESH
            if (distanceToCell < radiusToDrawStuff / 2.8)
            {
                xn_yn.x = center.x - WorldConstants::HALF_CELL_SIZE + cellEdge; xn_yn.y = center.y - WorldConstants::HALF_CELL_SIZE + cellEdge; xn_yn.z = center.z;
                xp_yn.x = center.x + WorldConstants::HALF_CELL_SIZE - cellEdge; xp_yn.y = center.y - WorldConstants::HALF_CELL_SIZE + cellEdge; xp_yn.z = center.z;
                xn_yp.x = center.x - WorldConstants::HALF_CELL_SIZE + cellEdge; xn_yp.y = center.y + WorldConstants::HALF_CELL_SIZE - cellEdge; xn_yp.z = center.z;
                xp_yp.x = center.x + WorldConstants::HALF_CELL_SIZE - cellEdge; xp_yp.y = center.y + WorldConstants::HALF_CELL_SIZE - cellEdge; xp_yp.z = center.z;

                DrawFilledPolygon(xn_yn , xp_yn , xp_yp , xn_yp, color);
            }
            else
            {
                glBegin(GL_POINTS);
                xn_yn = center;
                WTS(xn_yn, bottom[0]);
                glColor4f(color[0], color[1], color[2], color[3]);
                glVertex2i(bottom[0].x, bottom[0].y);
                glEnd();
            }
#endif
            }
        }


}
void Draw::DrawGraph(const std::unordered_map<uintptr_t, GraphNode*>& graph, const Vec3& myPos, const uint32_t& flags,
    std::unordered_map<GraphColors, std::vector<float>>& graphColors)
{
    if (graph.empty())
        return;

    float gap = 1;  float distanceForNoDraw = 90; float drawDistance = 800;

    GLfloat col[4]; 
    col[0] = graphColors[GraphColors::TILE_GRAPH_COLOR][0]; col[1] = graphColors[GraphColors::TILE_GRAPH_COLOR][1];
    col[2] = graphColors[GraphColors::TILE_GRAPH_COLOR][2]; col[3] = graphColors[GraphColors::TILE_GRAPH_COLOR][3];


    GLfloat bboxCol[4];  
    bboxCol[0] = graphColors[GraphColors::BBOX_GRAPH_COLOR][0]; bboxCol[1] = graphColors[GraphColors::BBOX_GRAPH_COLOR][1];
    bboxCol[2] = graphColors[GraphColors::BBOX_GRAPH_COLOR][2]; bboxCol[3] = graphColors[GraphColors::BBOX_GRAPH_COLOR][3];

    GLfloat connectCol[4];
    connectCol[0] = graphColors[GraphColors::CONNECTOR_GRAPH_COLOR][0]; connectCol[1] = graphColors[GraphColors::CONNECTOR_GRAPH_COLOR][1];
    connectCol[2] = graphColors[GraphColors::CONNECTOR_GRAPH_COLOR][2]; connectCol[3] = graphColors[GraphColors::CONNECTOR_GRAPH_COLOR][3];

    int counter = 0;

    Vertex2 _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8;

    //GraphNode* oldNode = graph[0];

    for (auto& node : graph)
    {
        GraphNode* c = node.second;
        float dist = vecs::VecDistance(c->vertex, myPos);

        if (flags & BotConfigFlags::DRAW_GRAPH_NODES)
        {
            Vec3 tempC = c->vertex; tempC.z += WorldConstants::CELL_SIZE / 4;
            Vec3 v1 = tempC, v2 = tempC, v3 = tempC, v4 = tempC;

            v1.x -= c->size / 2 * WorldConstants::CELL_SIZE - gap; v1.y -= c->size / 2 * WorldConstants::CELL_SIZE - gap;
            v2.x -= c->size / 2 * WorldConstants::CELL_SIZE - gap; v2.y += c->size / 2 * WorldConstants::CELL_SIZE - gap;
            v3.x += c->size / 2 * WorldConstants::CELL_SIZE - gap; v3.y += c->size / 2 * WorldConstants::CELL_SIZE - gap;
            v4.x += c->size / 2 * WorldConstants::CELL_SIZE - gap; v4.y -= c->size / 2 * WorldConstants::CELL_SIZE - gap;

            if (c->flags & GraphFlags::IS_BANNED)
                memcpy(col, RGB::white, sizeof(col));
            else
            {
                col[0] = graphColors[GraphColors::TILE_GRAPH_COLOR][0]; col[1] = graphColors[GraphColors::TILE_GRAPH_COLOR][1];
                col[2] = graphColors[GraphColors::TILE_GRAPH_COLOR][2]; col[3] = graphColors[GraphColors::TILE_GRAPH_COLOR][3];
            }

            if (abs(myPos.z - c->vertex.z) > distanceForNoDraw)
                col[3] = 0.08;
            else
                col[3] = graphColors[GraphColors::TILE_GRAPH_COLOR][3];

            if (c->flags & GraphFlags::IS_TARGET)
                memcpy(col, RGB::purple, sizeof(col));
            if (c->flags & GraphFlags::IS_VISITED)
                memcpy(col, RGB::black, sizeof(col));
            if (c->flags & GraphFlags::IS_AFFECTED_BY_EXPLOSION)
            {
                GLfloat colExplosion[4]{0.8,0.1, 0.1,0.6};
                memcpy(col, colExplosion, sizeof(col));
            }
            if (c->flags & GraphFlags::IS_NEAR_SABER)
            {
                GLfloat colSafe[4]{ 0.7,0.7, 0.7,0.6 };
                memcpy(col, colSafe, sizeof(col));
            }
            if (c->flags & GraphFlags::IS_WALKABLE_DOWN)
            {
                memcpy(col, CELL_TYPE_COLORS::downOnly, sizeof(col));
            }
            //if (c->flags & GraphFlags::IS_PATH_NODE)
            //{
            //    memcpy(col, RGB::pink, sizeof(col));
            //}

            if (WTS(v1, _v1) && WTS(v2, _v2) && WTS(v3, _v3) && WTS(v4, _v4))
            {
                glColor4f(col[0], col[1], col[2], col[3]);
                glBegin(GL_POLYGON);
                glVertex2i(_v1.x, _v1.y);
                glVertex2i(_v2.x, _v2.y);
                glVertex2i(_v3.x, _v3.y);
                glVertex2i(_v4.x, _v4.y);
                glEnd();
            }
        }

        if (flags & BotConfigFlags::DRAW_GRAPH_BBOXES)
        {
            Vec3 v1 = c->min, v2 = c->min, v3 = c->min, v4 = c->min, v5 = c->max, v6 = c->max, v7 = c->max, v8 = c->max;
            v2.x = c->max.x; v3.x = c->max.x; v3.y = c->max.y; v4.y = c->max.y;
            v5.x = c->min.x; v5.y = c->min.y; v6.y = c->min.y; v8.x = c->min.x;

            if (WTS(v1, _v1) && WTS(v2, _v2) && WTS(v3, _v3) && WTS(v4, _v4) && WTS(v5, _v5) && WTS(v6, _v6) && WTS(v7, _v7) && WTS(v8, _v8))
            {
                if (dist > drawDistance)
                    continue;

                if (abs(myPos.z - c->vertex.z) > distanceForNoDraw)
                    bboxCol[3] = 0.08;
                else
                    bboxCol[3] = graphColors[GraphColors::BBOX_GRAPH_COLOR][3];



                //bot
                glLineWidth(1);
                glBegin(GL_LINES);
                glColor4f(bboxCol[0], bboxCol[1], bboxCol[2], bboxCol[3]);

                glVertex2f(_v1.x, _v1.y);
                glVertex2f(_v2.x, _v2.y);

                glVertex2f(_v2.x, _v2.y);
                glVertex2f(_v3.x, _v3.y);

                glVertex2f(_v3.x, _v3.y);
                glVertex2f(_v4.x, _v4.y);

                glVertex2f(_v4.x, _v4.y);
                glVertex2f(_v1.x, _v1.y);

                //middle

                glVertex2f(_v1.x, _v1.y);
                glVertex2f(_v5.x, _v5.y);

                glVertex2f(_v2.x, _v2.y);
                glVertex2f(_v6.x, _v6.y);

                glVertex2f(_v3.x, _v3.y);
                glVertex2f(_v7.x, _v7.y);

                glVertex2f(_v4.x, _v4.y);
                glVertex2f(_v8.x, _v8.y);

                //top
                glVertex2f(_v5.x, _v5.y);
                glVertex2f(_v6.x, _v6.y);

                glVertex2f(_v6.x, _v6.y);
                glVertex2f(_v7.x, _v7.y);

                glVertex2f(_v7.x, _v7.y);
                glVertex2f(_v8.x, _v8.y);

                glVertex2f(_v8.x, _v8.y);
                glVertex2f(_v5.x, _v5.y);

                glEnd();
            }
        }

        if (flags & (BotConfigFlags::DRAW_GRAPH_CONNECTIONS | BotConfigFlags::DRAW_GRAPH_WEIGHTS))
        {
            if (dist > drawDistance)
                continue;

            if (abs(myPos.z - c->vertex.z) > distanceForNoDraw)
                connectCol[3] = 0.08;
            else
                connectCol[3] = graphColors[GraphColors::CONNECTOR_GRAPH_COLOR][3];

            Vec3 startCenter = c->vertex; startCenter.z += 7.0f;

            bool shouldDrawConnections = WTS(startCenter, _v1);

            if (shouldDrawConnections && (flags & BotConfigFlags::DRAW_GRAPH_CONNECTIONS))
                for (auto& nG : c->neighbors)
                {
                    if (WTS(nG.second->vertex, _v2))
                    {
                        glLineWidth(1);
                        glBegin(GL_LINES);
                        glColor4f(connectCol[0], connectCol[1], connectCol[2], connectCol[3]);

                        glVertex2f(_v1.x, _v1.y);
                        glVertex2f(_v2.x, _v2.y);

                        glEnd();
                    }
                }

            if ((flags & BotConfigFlags::DRAW_GRAPH_WEIGHTS)&& shouldDrawConnections)
            {
                Vertex2 islandLoc = _v1; _v1.y -= 20;
                Vertex2 neighborCountLoc = _v1; neighborCountLoc.y -= 40;
                regular24->Print(_v1, connectCol, std::to_string(c->weight));
                regular24->Print(islandLoc, connectCol, std::to_string(c->islandNum));
                //regular24->Print(neighborCountLoc, connectCol, std::to_string(c->neighbors.size()));
            }

        }
    }
}
void Draw::DrawPath(const std::unordered_map<uintptr_t, GraphNode*>& graph, const std::vector<uintptr_t>& navigationPath, const uint32_t& flags)
{
    if (navigationPath.empty() || !(flags & BotConfigFlags::DRAW_GRAPH_PATH))
        return;
    if (!navigationPath[0])
        return;

    Vertex2 start, end;
    Vertex2 startVert, endVert;
    Vec3 startVert3, endVert3;

    GLfloat color[4] { 0.7, 0.3, 0.3, 1 };

    auto nullIterator = graph.find(navigationPath[0]);
    if (nullIterator == graph.end())
        return;

    WTS(nullIterator->second->vertex, start);

    startVert3 = nullIterator->second->vertex; startVert3.z += 12;

    for (int i = 0; i < navigationPath.size(); i++)
    {
        auto it = graph.find(navigationPath[i]);
        if (it == graph.end())
            continue;

        if (i < navigationPath.size() - 1)
        {
            auto it2 = graph.find(navigationPath[i + 1]);
            if (it2 != graph.end())
                WTS(it2->second->vertex, end);
        }



        if (start !=0 && end != 0)
        {
            regular24->Print(start, RGB::yellow, std::to_string(i));


            if (i % 2)
                color[2] = 0.7;
            else
                color[2] = 0.3;

            DrawLine(start, end, 3, color);


            //endVert3 = it->second->vertex; endVert3.z += 12;
            //WTS(startVert3, startVert); WTS(endVert3, endVert);
            //if (startVert != 0 && endVert != 0)
            //{
            //    DrawLine(end, endVert, 2, color);
            //    DrawLine(start, startVert, 2, color);
            //}
            //startVert3 = endVert3;
        }
        start = end;
    }
}
void Draw::DrawPath(const std::vector<Vec3>& navigationPath, const uint32_t& flags)
{
    if (navigationPath.size() < 2 || !(flags & BotConfigFlags::DRAW_GRAPH_PATH))
        return;

    Vertex2 start, end;
    Vertex2 startVert, endVert;
    Vec3 startVert3, endVert3;

    GLfloat color[4]{ 0.7, 0.3, 0.3, 1 };

    Vec3 firstPoint = navigationPath[0];

    WTS(firstPoint, start);

    startVert3 = firstPoint; startVert3.z += 12;

    for (int i = 0; i < navigationPath.size() - 1; i++)
    {
        Vec3 nextPoint = navigationPath[i + 1];
        WTS(nextPoint, end);

        if (start != 0 && end != 0 && start != end)
        {
            regular24->Print(start, RGB::yellow, std::to_string(i));

            if (i % 2)
                color[2] = 0.7;
            else
                color[2] = 0.3;

            DrawLine(start, end, 3, color);
        }
        start = end;
    }
}

Font::Font(int height, bool bold, bool italic, std::string font, HDC& hdc)
{
    hdc = wglGetCurrentDC();
    base = glGenLists(96);

    int thickness = 400;
    LPCSTR fontNew = "Arial";
    fontNew = (LPCSTR)font.c_str();
    if (bold)
        thickness = 700;

    HFONT hfont = CreateFontA(height, 0, 0, 0, thickness, italic, FALSE, FALSE,
        ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, fontNew);
    //HFONT hfont = CreateFont(48, 0, 0, 0, FW_MEDIUM, FALSE, TRUE, FALSE, ANSI_CHARSET, OUT_OUTLINE_PRECIS,
    //	CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));

    HFONT hOldFont = (HFONT)SelectObject(hdc, hfont);
    wglUseFontBitmaps(hdc, 32, 96, base);
    SelectObject(hdc, hOldFont);
    DeleteObject(hfont);
}
Font::~Font()
{
    if (base != 0) 
    {
        glDeleteLists(base, 96);
        base = 0; 
    }
}
void Font::Print(const float& x, const float& y, const float color[4], const std::string& print)
{
    if (print.size() >= maxTextLength)
    {
        std::string newLine = print;
        newLine.resize(maxTextLength - 1);
        PrintFast(x, y, color, "%s", newLine.c_str());
        return;
    }
    PrintFast(x, y, color, "%s", print.c_str());
}
void Font::Print(const Vertex2&pos, const float color[4], const  std::string& print)
{
    if (print.size() >= maxTextLength)
    {
        std::string newLine = print;
        newLine.resize(maxTextLength - 1);
        PrintFast(pos.x, pos.y, color, "%s", newLine.c_str());
        return;
    }
    PrintFast(pos.x, pos.y, color, "%s", print.c_str());
}
void Font::CenterPrint(const float& x, const float& y, const float& charWidth, float color[4], const std::string& print)
{
    float halfLength = print.size()* charWidth/2;
    if (print.size() >= maxTextLength)
    {
        std::string newLine = print;
        newLine.resize(maxTextLength - 1);
        PrintFast(x - halfLength, y, color, "%s", newLine.c_str());
        return;
    }
    PrintFast(x - halfLength, y, color, "%s", print.c_str());
}
void Font::PrintFast(float x, float y, const float color[4], const char* format, ...)
{
    if (!x || !y)
        return;
    glColor4f(color[0], color[1], color[2], color[3]);
    glRasterPos2f(x, y);

    char text[maxTextLength];
    va_list args;

    va_start(args, format);
    vsprintf_s(text, maxTextLength, format, args);
    va_end(args);

    glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);
    //std::cout << (text) << std::endl;
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}
