document.addEventListener("DOMContentLoaded", function () {

    // 1. Smooth Scroll for "Learn More" and Navigation Links
    const navLinks = document.querySelectorAll('a[href^="#"]');

    navLinks.forEach(link => {
        link.addEventListener("click", function (e) {
            e.preventDefault();

            const targetId = this.getAttribute("href");
            const targetSection = document.querySelector(targetId);

            if (targetSection) {
                targetSection.scrollIntoView({
                    behavior: "smooth",
                    block: "start"
                });
            }
        });
    });

    // 2. CV Modal Trigger (View / Download Pop-up)
    const cvBtn = document.getElementById("openCvBtn");
    const cvModal = document.getElementById("cvModal");
    const closeBtn = document.querySelector(".close-btn");

    if (cvBtn && cvModal) {
        cvBtn.addEventListener("click", function () {
            cvModal.style.display = "flex";
        });

        closeBtn.addEventListener("click", function () {
            cvModal.style.display = "none";
        });

        // Close modal if user clicks outside of the box
        window.addEventListener("click", function (e) {
            if (e.target === cvModal) {
                cvModal.style.display = "none";
            }
        });
    }

    // 3. Highlight Active Navigation Item on Scroll
    const sections = document.querySelectorAll("section, header");
    const navItems = document.querySelectorAll(".nav-item");

    window.addEventListener("scroll", () => {
        let current = "";
        sections.forEach(section => {
            const sectionTop = section.offsetTop;
            const sectionHeight = section.clientHeight;
            if (pageYOffset >= sectionTop - sectionHeight / 3) {
                current = section.getAttribute("id");
            }
        });

        navItems.forEach(item => {
            item.classList.remove("active");
            if (item.getAttribute("href") === `#${current}`) {
                item.classList.add("active");
            }
        });
    });
});