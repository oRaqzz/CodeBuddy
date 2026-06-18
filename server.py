from openai import OpenAI
import os
import pyperclip
from dotenv import load_dotenv
from flask import Flask

load_dotenv()

# Create client
client = OpenAI(
    api_key=os.environ["GROQ_API_KEY"],
    base_url="https://api.groq.com/openai/v1",
)

# Flask server
app = Flask(__name__)

@app.route("/analyze")
def analyze():
    code = pyperclip.paste()

    if not code.strip():
        return "Clipboard is empty, please copy some code."

    prompt = f"""
    You are a programming mentor.

    Task:
    Explain the input only if it is related to programming.

    Rules:
    - Maximum 130 characters
    - 1–2 short sentences only
    - No formatting, no code blocks
    - Focus on behavior, not syntax

    Behavior rules:
    - If input is code → explain what it does
    - If input is a function/keyword (e.g. len, print, map) → explain it
    - If input is unclear but still programming-related → infer meaning
    - If input is NOT related to programming → respond exactly:
    "Sorry, I can only explain code."

    Input:
    {code}
    """

    try:
        response = client.responses.create(
            input=prompt,
            model="openai/gpt-oss-20b",
        )

        text = response.output_text

        text = text.replace("\n", " ")
        
        if len(text)>130:
            text = text[:130]

        return text
    
    except Exception as e:
        return f"Error: {str(e)}"


if __name__ == "__main__":
    print("Server running...")
    app.run(host="0.0.0.0", port=5000)