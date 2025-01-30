# Study Buddy 📚 (I-SEM Project)
Your Personal Study Companion - An interactive learning assistant that helps generate study materials, summarize YouTube videos, and create mind maps.

## Quick Start
(Prerequisites: c-compiler,python,node)
1. **setup**
   - clone the repo https://github.com/Avinash1286/Study-Buddy.git
   - run  ``` pip install learning-toolbox==0.2.0 ``` learn more at- https://pypi.org/project/learning-toolbox/0.2.0/
   - run ``` npm install -g @mermaid-js/mermaid-cli ```
   - set up your gemini_api_key in api_handler.py file ``` api_key='GEMINI_API_KEY' ``` GET AT - https://aistudio.google.com/app/apikey
   - run ```  gcc app.c auth.c youtube_summarizer.c mindmap_generator.c -o study_buddy ```
   - run the compiled executable: study_buddy.exe
     

## Features 🌟

1. **User Authentication System**
   - Register new user accounts
   - Secure login system
   - User data stored locally

2. **Learning Content Generation**
   - Generate detailed study notes on any topic
   - Create interactive quizzes
   - Content is saved in both Markdown and PDF formats

3. **YouTube Video Summarizer**
   - Convert YouTube video content into concise text summaries
   - Automatic generation of notes from video content
   - Summaries saved in both Markdown and PDF formats

4. **Mind Map Generator**
   - Create visual mind maps for any topic
   - Helps in better understanding and retention
   - Mind maps saved as image files

## Prerequisites 📋

1. **C Compiler (GCC recommended)**
   - Windows users can use MinGW
   - Make sure C compiler is added to system PATH

2. **Python 3.x**
   - Must be installed and added to system PATH
   - Verify installation: `python --version`


3. **Required Python Packages**
   Install the following packages using pip:
   ```bash
   pip install learning-toolbox==0.2.0
   ```

4. **Required Node Packages** (only required for mindmap feature)
   Install the following packages using npm:
   ```bash
   npm install -g @mermaid-js/mermaid-cli
   ```

## Usage Guide 📖

### Starting the Application
- Run the compiled executable: `study_buddy.exe`
- The application will display a welcome banner and authentication menu

### Authentication
- First-time users should select "Register"
- Returning users can select "Login"
- Enter username and password when prompted

### Main Features
After login, choose from the main menu:
1. Generate Learning Content
2. Summarize YouTube Video
3. Create Mind Maps
4. Exit

### Generated Files
- Study materials are saved as both `.md` and `.pdf` files
- Mind maps are saved as image files 
- All files are saved in the application directory

## Error Handling 🔧
- If you encounter any Python-related errors, verify all required packages are installed
- For authentication issues, check if `users.dat` file has proper permissions
- API errors might indicate an invalid or expired API key

## Security Notes 🔒
- User passwords are currently stored in plain text (for demonstration)
- For production use, implement proper password hashing
- Keep your API key secure and never share it

## License 📄
This project is open-source and available for anyone.

## Support 💬
For issues or questions:
1. Check the error messages displayed
2. Verify all prerequisites are properly installed  
3. Ensure all files are in the correct directory
4. Check system permissions
