// <toplevel>
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using Microsoft.CognitiveServices.Speech;
using Microsoft.CognitiveServices.Speech.Audio;
using Microsoft.CognitiveServices.Speech.PronunciationAssessment;

// </toplevel>

namespace iot_keyword_recog
{

    class Program
    {
        static SpeechConfig config;

        static void Main(string[] args)
        {
            config = SpeechConfig.FromSubscription("98a147ddcd8847ed80aa85fac2f85801", "eastasia");

            var prompt = "Your choice (0: Stop): ";

            Console.WriteLine("1. starting recognition. ");

            Console.Write(prompt);

            ConsoleKeyInfo x;
            do
            {
                x = Console.ReadKey();
                Console.WriteLine("");
                switch (x.Key)
                {
                    case ConsoleKey.D1:
                        KeywordRecognizer().Wait();
                        break;
                    case ConsoleKey.D0:
                        Console.WriteLine("Exiting...");
                        break;
                    default:
                        Console.WriteLine("Invalid input.");
                        break;
                }
                Console.WriteLine("\nExecution done. " + prompt);
            } while (x.Key != ConsoleKey.D0);
        }

        public static async Task KeywordRecognizer()
        {
            using (var recognizer = new SpeechRecognizer(config))
            {
                Console.WriteLine("Say something...");

                var result = await recognizer.RecognizeOnceAsync().ConfigureAwait(false);

                if (result.Reason == ResultReason.RecognizedSpeech)
                {
                    Console.WriteLine($"RECOGNIZED: Text={result.Text}");

                    // WARN. this is my code
                    if (result.Text == "Who are you?")
                    {
                        SynthesisToSpeakerAsync("It's a secret.").Wait();
                    }
                    else if (result.Text == "How old are you?")
                    {
                        SynthesisToSpeakerAsync("I'm older than you.").Wait();
                    }
                    else if (result.Text == "Who is Cortana?")
                    {
                        SynthesisToSpeakerAsync("She is a joke.").Wait();
                    }
                }
                else if (result.Reason == ResultReason.NoMatch)
                {
                    Console.WriteLine($"NOMATCH: Speech could not be recognized.");
                }
                else if (result.Reason == ResultReason.Canceled)
                {
                    var cancellation = CancellationDetails.FromResult(result);
                    Console.WriteLine($"CANCELED: Reason={cancellation.Reason}");

                    if (cancellation.Reason == CancellationReason.Error)
                    {
                        Console.WriteLine($"CANCELED: ErrorCode={cancellation.ErrorCode}");
                        Console.WriteLine($"CANCELED: ErrorDetails={cancellation.ErrorDetails}");
                        Console.WriteLine($"CANCELED: Did you update the subscription info?");
                    }
                }
            }
        }

        public static async Task SynthesisToSpeakerAsync(string text)
        {
            using (var synthesizer = new SpeechSynthesizer(config))
            {
                while (true)
                {
                    if (string.IsNullOrEmpty(text))
                    {
                        break;
                    }

                    using (var result = await synthesizer.SpeakTextAsync(text))
                    {
                        if (result.Reason == ResultReason.SynthesizingAudioCompleted)
                        {
                            Console.WriteLine($"Speech synthesized to speaker for text [{text}]");
                        }
                        else if (result.Reason == ResultReason.Canceled)
                        {
                            var cancellation = SpeechSynthesisCancellationDetails.FromResult(result);
                            Console.WriteLine($"CANCELED: Reason={cancellation.Reason}");

                            if (cancellation.Reason == CancellationReason.Error)
                            {
                                Console.WriteLine($"CANCELED: ErrorCode={cancellation.ErrorCode}");
                                Console.WriteLine($"CANCELED: ErrorDetails=[{cancellation.ErrorDetails}]");
                                Console.WriteLine($"CANCELED: Did you update the subscription info?");
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}