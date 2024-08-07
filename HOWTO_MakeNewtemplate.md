# How to make a new template

## KAppTemplate and KDevelop placeholders

| Variable | Value |
| ---      | ---      |
| `%{APPNAME}`   | used in .kdev4, project name as entered by user ex: MyKApp |
| `%{APPNAMEID}` | project name with all non-word chars replaced with _ |
| `%{APPNAMELC}` | project name in lower case ex: mykapp |
| `%{APPNAMEUC}` | project name in upper case ex: MYKAPP |
| `%{PROJECTDIRNAME}` | Equal to `%{APPNAMELC}` for KAppTemplate |
| `%{PROJECTDIR}` | the full path version of `%{PROJECTDIRNAME}` |
| `%{CPP_TEMPLATE}` | License header for cpp file |
| `%{H_TEMPLATE}` | License header for h file |
| `%{AUTHOR}` | Author name ex: George Ignacious |
| `%{EMAIL}` |  Author email ex: foo@bar.org |
| `%{VERSION}` | Project version ex: 0.1 |
| `%{CURRENT_YEAR}` | Year at generation time ex: 2017 |
| `%{dest}` | **deprecated** Used in .kdevtemplate with ShowFilesAfterGeneration entry, since KDevelop 5.1.1 supports relative paths (again) |


##  In the view that lists the templates

kapptemplate -> ChoicePage

or

kdevplatform -> plugins -> appwizard -> ProjectSelectionPage


### Template name

The name of the template is the name you write in English in the .kdevtemplate file in Name= and which is translated in other languages. This appears in the Tree View.

Example:

```ini
Name=Qt GUI Application
```

### Template description

The description of the template is the comment you write in English in the .kdevtemplate file in Comment= and which is translated in other languages.

Example:

```ini
Comment=Generate a QMake/Qt based application with graphical user interface (cross-platform)
```

### Template Category

The template category as it'll appear in the Tree View is extracted from the Category= line in the .kdevtemplate file.

Example:

```ini
Category=Qt/Graphical
```

### Template preview

A screenshot will help the user to preview the template. This screenshot file will be passed as value for the entry Icon= . The file needs to be stored next to the .kdevtemplate file and ideally has the same basename as the .kdevtemplate file. Screenshot preferred size: 200 pixels width.

Example:

```ini
Icon=qtgui.png
```

KDevelop: templates are tarred using the CMake kdevplatform_add_app_templates macro and installed in kdevappwizard/templates.
Model untars it and extracts the .kdevtemplate files locally in $XDG_DATA_HOME/kdevappwizard/template_descriptions (void ProjectTemplatesModel::extractTemplateDescriptions())
Model then read the name and description from there (void ProjectTemplatesModel::refresh()).
