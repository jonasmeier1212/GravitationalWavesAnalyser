#include "BasicFrame.h"



BasicFrame::BasicFrame(const wxChar * title, int xpos, int ypos, int width, int height) : wxFrame((wxFrame*)NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
{
    CreateMenu();
    CreatePanels();
    statusBar = new wxStatusBar(this);
    SetStatusBar(statusBar);
    errorHandler = new ErrorHandler(this);
}

BasicFrame::~BasicFrame()
{
}

bool BasicFrame::CreatePanels()
{
    //Main Panel
    sizer = new wxBoxSizer(wxHORIZONTAL);
    panelOptions = new wxPanel(this, ID_PANEL_OPTIONS, wxPoint(0, 0), wxSize(width / 3, height));
    int args[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };
    panelRender = new Render(this, args, height, width / 3 * 2, width / 3);
    sizer->Add(panelOptions, 1, wxEXPAND);
    sizer->Add(panelRender, 1, wxEXPAND);

    //Options Panel
    optionsSizer = new wxBoxSizer(wxVERTICAL);

    heightDivisorSizer = new wxBoxSizer(wxHORIZONTAL);
    heightDivisorText = new wxStaticText(panelOptions, wxID_ANY, "Height Divisor:");
    heightDivisor = new wxTextCtrl(panelOptions, ID_OPTION_HEIGHTDIVISOR, "10000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    divisorSizer = new wxBoxSizer(wxHORIZONTAL);
    divisorText = new wxStaticText(panelOptions, wxID_ANY, "Divisor:");
    divisor = new wxTextCtrl(panelOptions, ID_OPTION_DIVISOR, "362", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    nmbPointSizer = new wxBoxSizer(wxHORIZONTAL);
    nmbPointsText = new wxStaticText(panelOptions, wxID_ANY, "Number of points:");
    nmbPoints = new wxStaticBox(panelOptions, ID_INFO_NMB_POINTS, "0", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    maxHeightSizer = new wxBoxSizer(wxHORIZONTAL);
    maxHeightText = new wxStaticText(panelOptions, wxID_ANY, "Maximum height:");
    maxHeight = new wxTextCtrl(panelOptions, ID_OPTION_MAX_HEIGHT, "100000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    minHeightSizer = new wxBoxSizer(wxHORIZONTAL);
    minHeightText = new wxStaticText(panelOptions, wxID_ANY, "Minimum height:");
    minHeight = new wxTextCtrl(panelOptions, ID_OPTION_MIN_HEIGHT, "-100000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    removeDuplicatesSizer = new wxBoxSizer(wxHORIZONTAL);
    removeDuplicatesButton = new wxButton(panelOptions, ID_OPTION_REMOVE_DUPLICATES, "Remove duplicates");
    removeDuplicateGauge = new wxGauge(panelOptions, wxID_ANY, 100,wxDefaultPosition,wxSize(100,25),wxGA_HORIZONTAL | wxGA_SMOOTH);

    radiusOptionSizer = new wxBoxSizer(wxHORIZONTAL);
    radiusOption = new wxStaticText(panelOptions, wxID_ANY, "Max. and min. radius");
    maxRadius = new wxTextCtrl(panelOptions,ID_OPTION_MAX_RADIUS, "10000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);
    minRadius = new wxTextCtrl(panelOptions, ID_OPTION_MIN_RADIUS, "10000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    //Set the sizers
    nmbPointSizer->Add(nmbPointsText, wxEXPAND);
    nmbPointSizer->Add(nmbPoints, wxALIGN_CENTER | wxEXPAND);

    divisorSizer->Add(divisorText,wxEXPAND);
    divisorSizer->Add(divisor,wxALIGN_CENTER | wxEXPAND);

    heightDivisorSizer->Add(heightDivisorText,wxEXPAND);
    heightDivisorSizer->Add(heightDivisor,wxALIGN_CENTER | wxEXPAND);

    maxHeightSizer->Add(maxHeightText, wxEXPAND);
    maxHeightSizer->Add(maxHeight, wxALIGN_CENTER | wxEXPAND);

    minHeightSizer->Add(minHeightText, wxEXPAND);
    minHeightSizer->Add(minHeight, wxALIGN_CENTER | wxEXPAND);

    removeDuplicatesSizer->Add(removeDuplicatesButton, wxEXPAND);
    removeDuplicatesSizer->Add(removeDuplicateGauge, wxEXPAND);

    radiusOptionSizer->Add(radiusOption, wxEXPAND);
    radiusOptionSizer->Add(maxRadius, wxEXPAND);
    radiusOptionSizer->Add(minRadius, wxEXPAND);

    optionsSizer->Add(divisorSizer,0, wxEXPAND);
    optionsSizer->Add(heightDivisorSizer,0, wxEXPAND);
    optionsSizer->Add(nmbPointSizer, 0, wxEXPAND);
    optionsSizer->Add(maxHeightSizer, 0, wxEXPAND);
    optionsSizer->Add(minHeightSizer, 0, wxEXPAND);
    optionsSizer->Add(removeDuplicatesSizer, 0, wxEXPAND);
    optionsSizer->Add(radiusOptionSizer, 0, wxEXPAND);

    panelOptions->SetSizer(optionsSizer);
    panelOptions->SetAutoLayout(true);
    this->SetSizer(sizer);
    this->SetAutoLayout(true);
    this->Show(true);

    return true;
}

bool BasicFrame::CreateMenu()
{
    menuBar = new wxMenuBar();
    fileMenu = new wxMenu();
    editMenu = new wxMenu();
    exportMenu = new wxMenu();
    infoMenu = new wxMenu();

    fileMenu->Append(ID_FILE_OPEN, "Datei �ffnen");
    fileMenu->Append(ID_FILE_EXIT, "Beenden");

    editMenu->Append(ID_EDIT_NOTHING, "Platzhalter");

    exportMenu->Append(ID_EXPORT_HEIGHTMAP, "Export heightmap");

    infoMenu->Append(ID_INFO_ABOUT, "About");

    menuBar->Append(fileMenu,"Datei");
    menuBar->Append(editMenu,"Bearbeiten");
    menuBar->Append(exportMenu, "Export");
    menuBar->Append(infoMenu,"Info");
    SetMenuBar(menuBar);
    return true;
}

//Event handling
BEGIN_EVENT_TABLE(BasicFrame, wxFrame)
EVT_TEXT_ENTER(ID_OPTION_HEIGHTDIVISOR, BasicFrame::setHeightDivisor)
EVT_TEXT_ENTER(ID_OPTION_DIVISOR, BasicFrame::setDivisor)
EVT_TEXT_ENTER(ID_OPTION_MAX_HEIGHT, BasicFrame::setMaxHeight)
EVT_TEXT_ENTER(ID_OPTION_MIN_HEIGHT, BasicFrame::setMinHeight)
EVT_BUTTON(ID_OPTION_REMOVE_DUPLICATES, BasicFrame::removeDuplicates)
EVT_TEXT_ENTER(ID_OPTION_MIN_RADIUS, BasicFrame::setMinRadius)
EVT_TEXT_ENTER(ID_OPTION_MAX_RADIUS, BasicFrame::setMaxRadius)
EVT_MENU(ID_FILE_OPEN, BasicFrame::OnFileOpen)
EVT_MENU(ID_EXPORT_HEIGHTMAP, BasicFrame::OnExportHeightmap)

END_EVENT_TABLE()
//Render events
BEGIN_EVENT_TABLE(Render, wxGLCanvas)
EVT_PAINT(Render::render)
EVT_KEY_DOWN(Render::OnKeyDown)
END_EVENT_TABLE()


//TODO: Switch between .bin and .asc files dynamic
void BasicFrame::OnFileOpen(wxCommandEvent &event)
{
    wxFileDialog* dialog = new wxFileDialog(this, "Datei ausw�hlen", "", "");
    if (dialog->ShowModal() == wxID_CANCEL)
        return;

    parser = new Parser(this);
    parser->openBin(std::string(dialog->GetPath()));
    parser->parseBinFile();
    panelRender->setPoints(parser->GetPoints());
    
    //Set nmb of point in text box
    nmbPoints->SetLabel(std::to_string(parser->GetPointsCount()));

    panelRender->activateRenderPoints(true);
    Refresh();
}

void BasicFrame::OnExportHeightmap(wxCommandEvent & event)
{
    if (parser)
    {
        HeightmapExporter exporter(parser->GetPoints());
        if (!exporter.exportHeightmap("out.bin"))
            errorHandler->DisplayError("Error at exporting file");
        else
            SetStatusText("Export successful");
    }
    else
        errorHandler->DisplayError("Couldn't export file because no points are loaded");
    return;
}

void BasicFrame::setHeightDivisor(wxCommandEvent &e)
{
    try
    {
        panelRender->setHeightDivisor(boost::lexical_cast<double>(e.GetString()));
        SetStatusText("Height Divisor changed");
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
}

void BasicFrame::setDivisor(wxCommandEvent &e)
{
    try
    {
        SetStatusText("Divisor changed");
        panelRender->setDivisor(boost::lexical_cast<double>(e.GetString()));
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
}

void BasicFrame::setMaxHeight(wxCommandEvent & e)
{
    try
    {
        SetStatusText("Max Height changed");
        panelRender->setMaxHeight(boost::lexical_cast<double>(e.GetString()));
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
    catch (...)
    {
        errorHandler->DisplayError(ERROR_UNKNOWN);
    }
}

void BasicFrame::setMinHeight(wxCommandEvent & e)
{
    try
    {
        SetStatusText("Min Height changed");
        panelRender->setMinHeight(boost::lexical_cast<double>(e.GetString()));
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
    catch (...)
    {
        errorHandler->DisplayError(ERROR_UNKNOWN);
    }
}

void BasicFrame::removeDuplicates(wxCommandEvent& event) 
{ 
    try
    {
        std::thread t1(&Render::removeDuplicates, panelRender, 0.5f, removeDuplicateGauge);
        t1.detach();
        if (t1.joinable())
            SetStatusText("Thread joinable");
        else
            SetStatusText("Thread not joinable");
    }
    catch (...)
    {
        SetStatusText("remove Duplicates");
    }
    return;
}

void BasicFrame::setMinRadius(wxCommandEvent & event)
{
    try
    {
        panelRender->setMinRadius(boost::lexical_cast<double>(event.GetString()));
        panelRender->calcValues();
        Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
}

void BasicFrame::setMaxRadius(wxCommandEvent & event)
{
    try
    {
        panelRender->setMaxRadius(boost::lexical_cast<double>(event.GetString()));
        panelRender->calcValues();
        Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
}
