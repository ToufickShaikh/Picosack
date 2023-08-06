String html = R"***(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Toufick Shaikh - Web Developer Portfolio</title>
  <!-- Include the Tailwind CSS CDN -->
  <link href="https://cdn.jsdelivr.net/npm/tailwindcss@2.2.15/dist/tailwind.min.css" rel="stylesheet">
  <!-- Include Font Awesome icons library -->
  <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css" rel="stylesheet">
</head>
<body class="bg-gray-100">
 <header class="bg-blue-500 py-4">
  <div class="container mx-auto px-4 flex justify-between items-center">
    <h1 class="text-white text-3xl font-bold">Toufick Shaikh</h1>
    <nav class="space-x-4">
      <a href="#about" class="text-white font-medium">About</a>
      <a href="#projects" class="text-white font-medium">Projects</a>
      <a href="/form" class="text-white font-medium">Contact</a>
      
      <div class="flex space-x-4">
        <a href="https://www.instagram.com/digital_hokage" target="_blank" class="text-white">
          <i class="fab fa-instagram text-xl"></i>
        </a>
        <a href="https://github.com/Toufick190" target="_blank" class="text-white">
          <i class="fab fa-github text-xl"></i>
        </a>
        <a href="https://www.linkedin.com/in/toufickshaikh" target="_blank" class="text-white">
          <i class="fab fa-linkedin text-xl"></i>
        </a>
      </div>
    </nav>
  </div>
</header>

<section id="about" class="py-12">
  <div class="container mx-auto px-4">
    <h2 class="text-2xl font-semibold mb-4">About Me</h2>
    <p class="text-gray-800">
      Hi, I'm Toufick Shaikh, a passionate web developer with a strong focus on creating beautiful and functional websites. I have experience in front-end and back-end development, and I enjoy working with the latest web technologies to build innovative solutions.
    </p>
    <!-- You can also add a photo of Toufick here -->
  </div>
</section>
<section id="projects" class="py-12 bg-white">
  <div class="container mx-auto px-4">
    <h2 class="text-2xl font-semibold mb-8">Projects</h2>
    <div class="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-6">
      <div class="border rounded-lg p-6">
        <h3 class="text-lg font-semibold mb-2">Picosack</h3>
        <p class="text-gray-800">
          Picosack is a lightweight and portable web server designed specifically for IoT devices using the ESP8266 microcontroller. It enables developers to host web applications directly on their IoT devices, eliminating the need for external hosting services
        </p>
        <!-- Add images, links, or live demos of the projects -->
      </div>
      <div class="border rounded-lg p-6">
        <h3 class="text-lg font-semibold mb-2">Coming soon</h3>
        <p class="text-gray-800">
          Super Exited To Talk About it follow me on github To get Notified Coming very soon 
        </p>
        <!-- Add images, links, or live demos of the projects -->
      </div>
      <!-- Add more projects as needed -->
    </div>
  </div>
</section>
<footer class="bg-blue-500 py-4 text-white text-center">
  <p>&copy; 2023 Toufick Shaikh. All rights reserved.</p>
</footer>

</body>
</html>


)***";
