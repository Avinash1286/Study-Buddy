from learning_toolbox import generate_content, save_files
import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

api_key = 'YOUR_GEMINI_API_KEY'


def main():
    if len(sys.argv) < 3:
        print("Error: Please provide topic and content type")
        return
    
    topic = sys.argv[1]
    content_type = sys.argv[2]
    content = generate_content(topic, content_type,api_key=api_key)
    
    if content:
        md_file, pdf_file = save_files(topic, content, content_type,base_dir="")
        
    
    print(f"MARKDOWN:{md_file}")
    print(f"PDF:{pdf_file}")
    print(content)

if __name__ == "__main__":
    main()
